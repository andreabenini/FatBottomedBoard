/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/wdt.h>
#include <util/delay.h>
#include <stdint.h>
#include <usbdrv/usbdrv.h>
#include "usbconfig.h"
#include "host.h"
#include "report.h"
#include "host_driver.h"
#include "vusb.h"
#include "print.h"
#include "debug.h"
#include "usb_descriptor_common.h"

#ifdef RAW_ENABLE
#    include "raw_hid.h"
#endif

#if defined(CONSOLE_ENABLE)
#    define RBUF_SIZE 128
#    include "ring_buffer.h"
#endif

#define NEXT_INTERFACE __COUNTER__

/*
 * Interface indexes
 */
enum usb_interfaces {
    KEYBOARD_INTERFACE = NEXT_INTERFACE,
// It is important that the Raw HID interface is at a constant
// interface number, to support Linux/OSX platforms and chrome.hid
// If Raw HID is enabled, let it be always 1.
#ifdef RAW_ENABLE
    RAW_INTERFACE = NEXT_INTERFACE,
#endif
#if (defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE))
    MOUSE_EXTRA_INTERFACE = NEXT_INTERFACE,
#endif
#ifdef CONSOLE_ENABLE
    CONSOLE_INTERFACE = NEXT_INTERFACE,
#endif
    TOTAL_INTERFACES = NEXT_INTERFACE,
};

#define MAX_INTERFACES 2

#if (NEXT_INTERFACE - 1) > MAX_INTERFACES
#    error There are not enough available interfaces to support all functions. Please disable one or more of the following: Mouse Keys, Extra Keys, Raw HID, Console
#endif

static uint8_t vusb_keyboard_leds = 0;
static uint8_t vusb_idle_rate     = 0;

/* Keyboard report send buffer */
#define KBUF_SIZE 16
static report_keyboard_t kbuf[KBUF_SIZE];
static uint8_t           kbuf_head = 0;
static uint8_t           kbuf_tail = 0;

typedef struct {
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode[6];
} keyboard_report_t;

static keyboard_report_t keyboard_report;  // sent to PC

#define VUSB_TRANSFER_KEYBOARD_MAX_TRIES 10

/* transfer keyboard report from buffer */
void vusb_transfer_keyboard(void) {
    for (int i = 0; i < VUSB_TRANSFER_KEYBOARD_MAX_TRIES; i++) {
        if (usbInterruptIsReady()) {
            if (kbuf_head != kbuf_tail) {
                usbSetInterrupt((void *)&kbuf[kbuf_tail], sizeof(report_keyboard_t));
                kbuf_tail = (kbuf_tail + 1) % KBUF_SIZE;
                if (debug_keyboard) {
                    print("V-USB: kbuf[");
                    pdec(kbuf_tail);
                    print("->");
                    pdec(kbuf_head);
                    print("](");
                    phex((kbuf_head < kbuf_tail) ? (KBUF_SIZE - kbuf_tail + kbuf_head) : (kbuf_head - kbuf_tail));
                    print(")\n");
                }
            }
            break;
        }
        usbPoll();
        _delay_ms(1);
    }
}

/*------------------------------------------------------------------*
 * RAW HID
 *------------------------------------------------------------------*/
#ifdef RAW_ENABLE
#    define RAW_BUFFER_SIZE 32
#    define RAW_EPSIZE 8

static uint8_t raw_output_buffer[RAW_BUFFER_SIZE];
static uint8_t raw_output_received_bytes = 0;

void raw_hid_send(uint8_t *data, uint8_t length) {
    if (length != RAW_BUFFER_SIZE) {
        return;
    }

    uint8_t *temp = data;
    for (uint8_t i = 0; i < 4; i++) {
        while (!usbInterruptIsReady3()) {
            usbPoll();
        }
        usbSetInterrupt3(temp, 8);
        temp += 8;
    }
    while (!usbInterruptIsReady3()) {
        usbPoll();
    }
    usbSetInterrupt3(0, 0);
}

__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}

void raw_hid_task(void) {
    if (raw_output_received_bytes == RAW_BUFFER_SIZE) {
        raw_hid_receive(raw_output_buffer, RAW_BUFFER_SIZE);
        raw_output_received_bytes = 0;
    }
}
#endif

/*------------------------------------------------------------------*
 * Console
 *------------------------------------------------------------------*/
#ifdef CONSOLE_ENABLE
#    define CONSOLE_BUFFER_SIZE 32
#    define CONSOLE_EPSIZE 8

int8_t sendchar(uint8_t c) {
    rbuf_enqueue(c);
    return 0;
}

static inline bool usbSendData3(char *data, uint8_t len) {
    uint8_t retries = 5;
    while (!usbInterruptIsReady3()) {
        if (!(retries--)) {
            return false;
        }
        usbPoll();
    }

    usbSetInterrupt3((unsigned char *)data, len);
    return true;
}

void console_task(void) {
    if (!usbConfiguration) {
        return;
    }

    if (!rbuf_has_data()) {
        return;
    }

    // Send in chunks of 8 padded to 32
    char    send_buf[CONSOLE_BUFFER_SIZE] = {0};
    uint8_t send_buf_count                = 0;
    while (rbuf_has_data() && send_buf_count < CONSOLE_EPSIZE) {
        send_buf[send_buf_count++] = rbuf_dequeue();
    }

    char *temp = send_buf;
    for (uint8_t i = 0; i < 4; i++) {
        if (!usbSendData3(temp, 8)) {
            break;
        }
        temp += 8;
    }

    usbSendData3(0, 0);
    usbPoll();
}
#endif

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

host_driver_t *vusb_driver(void) { return &driver; }

static uint8_t keyboard_leds(void) { return vusb_keyboard_leds; }

static void send_keyboard(report_keyboard_t *report) {
    uint8_t next = (kbuf_head + 1) % KBUF_SIZE;
    if (next != kbuf_tail) {
        kbuf[kbuf_head] = *report;
        kbuf_head       = next;
    } else {
        debug("kbuf: full\n");
    }

    // NOTE: send key strokes of Macro
    usbPoll();
    vusb_transfer_keyboard();
}

typedef struct {
    uint8_t        report_id;
    report_mouse_t report;
} __attribute__((packed)) vusb_mouse_report_t;

static void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    vusb_mouse_report_t r = {.report_id = REPORT_ID_MOUSE, .report = *report};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&r, sizeof(vusb_mouse_report_t));
    }
#endif
}

#ifdef EXTRAKEY_ENABLE
static void send_extra(uint8_t report_id, uint16_t data) {
    static uint8_t  last_id   = 0;
    static uint16_t last_data = 0;
    if ((report_id == last_id) && (data == last_data)) return;
    last_id   = report_id;
    last_data = data;

    report_extra_t report = {.report_id = report_id, .usage = data};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&report, sizeof(report));
    }
}
#endif

static void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_SYSTEM, data);
#endif
}

static void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_CONSUMER, data);
#endif
}

/*------------------------------------------------------------------*
 * Request from host                                                *
 *------------------------------------------------------------------*/
static struct {
    uint16_t len;
    enum { NONE, SET_LED } kind;
} last_req;

usbMsgLen_t usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data;

    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) { /* class request type */
        if (rq->bRequest == USBRQ_HID_GET_REPORT) {
            debug("GET_REPORT:");
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (usbMsgPtr_t)&keyboard_report;
            return sizeof(keyboard_report);
        } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            debug("GET_IDLE: ");
            // debug_hex(vusb_idle_rate);
            usbMsgPtr = (usbMsgPtr_t)&vusb_idle_rate;
            return 1;
        } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            vusb_idle_rate = rq->wValue.bytes[1];
            debug("SET_IDLE: ");
            debug_hex(vusb_idle_rate);
        } else if (rq->bRequest == USBRQ_HID_SET_REPORT) {
            debug("SET_REPORT: ");
            // Report Type: 0x02(Out)/ReportID: 0x00(none) && Interface: 0(keyboard)
            if (rq->wValue.word == 0x0200 && rq->wIndex.word == 0) {
                debug("SET_LED: ");
                last_req.kind = SET_LED;
                last_req.len  = rq->wLength.word;
            }
            return USB_NO_MSG;  // to get data in usbFunctionWrite
        } else {
            debug("UNKNOWN:");
        }
    } else {
        debug("VENDOR:");
        /* no vendor specific requests implemented */
    }
    debug("\n");
    return 0; /* default for not implemented requests: return no data back to host */
}

uchar usbFunctionWrite(uchar *data, uchar len) {
    if (last_req.len == 0) {
        return -1;
    }
    switch (last_req.kind) {
        case SET_LED:
            debug("SET_LED: ");
            debug_hex(data[0]);
            debug("\n");
            vusb_keyboard_leds = data[0];
            last_req.len       = 0;
            return 1;
            break;
        case NONE:
        default:
            return -1;
            break;
    }
    return 1;
}

void usbFunctionWriteOut(uchar *data, uchar len) {
#ifdef RAW_ENABLE
    // Data from host must be divided every 8bytes
    if (len != 8) {
        debug("RAW: invalid length");
        raw_output_received_bytes = 0;
        return;
    }

    if (raw_output_received_bytes + len > RAW_BUFFER_SIZE) {
        debug("RAW: buffer full");
        raw_output_received_bytes = 0;
    } else {
        for (uint8_t i = 0; i < 8; i++) {
            raw_output_buffer[raw_output_received_bytes + i] = data[i];
        }
        raw_output_received_bytes += len;
    }
#endif
}

/*------------------------------------------------------------------*
 * Descriptors                                                      *
 *------------------------------------------------------------------*/

const PROGMEM uchar keyboard_hid_report[] = {
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x06,  // Usage (Keyboard)
    0xA1, 0x01,  // Collection (Application)
    // Modifiers (8 bits)
    0x05, 0x07,  //   Usage Page (Keyboard/Keypad)
    0x19, 0xE0,  //   Usage Minimum (Keyboard Left Control)
    0x29, 0xE7,  //   Usage Maximum (Keyboard Right GUI)
    0x15, 0x00,  //   Logical Minimum (0)
    0x25, 0x01,  //   Logical Maximum (1)
    0x95, 0x08,  //   Report Count (8)
    0x75, 0x01,  //   Report Size (1)
    0x81, 0x02,  //   Input (Data, Variable, Absolute)
    // Reserved (1 byte)
    0x95, 0x01,  //   Report Count (1)
    0x75, 0x08,  //   Report Size (8)
    0x81, 0x03,  //   Input (Constant)
    // Keycodes (6 bytes)
    0x05, 0x07,        //   Usage Page (Keyboard/Keypad)
    0x19, 0x00,        //   Usage Minimum (0)
    0x29, 0xFF,        //   Usage Maximum (255)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x95, 0x06,        //   Report Count (6)
    0x75, 0x08,        //   Report Size (8)
    0x81, 0x00,        //   Input (Data, Array, Absolute)

    // Status LEDs (5 bits)
    0x05, 0x08,  //   Usage Page (LED)
    0x19, 0x01,  //   Usage Minimum (Num Lock)
    0x29, 0x05,  //   Usage Maximum (Kana)
    0x95, 0x05,  //   Report Count (5)
    0x75, 0x01,  //   Report Size (1)
    0x91, 0x02,  //   Output (Data, Variable, Absolute)
    // LED padding (3 bits)
    0x95, 0x01,  //   Report Count (1)
    0x75, 0x03,  //   Report Size (3)
    0x91, 0x03,  //   Output (Constant)
    0xC0         // End Collection
};

#ifdef RAW_ENABLE
const PROGMEM uchar raw_hid_report[] = {
    0x06, RAW_USAGE_PAGE_LO, RAW_USAGE_PAGE_HI,  // Usage Page (Vendor Defined)
    0x09, RAW_USAGE_ID,                          // Usage (Vendor Defined)
    0xA1, 0x01,                                  // Collection (Application)
    // Data to host
    0x09, 0x62,             //   Usage (Vendor Defined)
    0x15, 0x00,             //   Logical Minimum (0)
    0x26, 0xFF, 0x00,       //   Logical Maximum (255)
    0x95, RAW_BUFFER_SIZE,  //   Report Count
    0x75, 0x08,             //   Report Size (8)
    0x81, 0x02,             //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x63,             //   Usage (Vendor Defined)
    0x15, 0x00,             //   Logical Minimum (0)
    0x26, 0xFF, 0x00,       //   Logical Maximum (255)
    0x95, RAW_BUFFER_SIZE,  //   Report Count
    0x75, 0x08,             //   Report Size (8)
    0x91, 0x02,             //   Output (Data, Variable, Absolute)
    0xC0                    // End Collection
};
#endif

#if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
const PROGMEM uchar mouse_extra_hid_report[] = {
#    ifdef MOUSE_ENABLE
    // Mouse report descriptor
    0x05, 0x01,             // Usage Page (Generic Desktop)
    0x09, 0x02,             // Usage (Mouse)
    0xA1, 0x01,             // Collection (Application)
    0x85, REPORT_ID_MOUSE,  //   Report ID
    0x09, 0x01,             //   Usage (Pointer)
    0xA1, 0x00,             //   Collection (Physical)
    // Buttons (5 bits)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (Button 1)
    0x29, 0x05,  //     Usage Maximum (Button 5)
    0x15, 0x00,  //     Logical Minimum (0)
    0x25, 0x01,  //     Logical Maximum (1)
    0x95, 0x05,  //     Report Count (5)
    0x75, 0x01,  //     Report Size (1)
    0x81, 0x02,  //     Input (Data, Variable, Absolute)
    // Button padding (3 bits)
    0x95, 0x01,  //     Report Count (1)
    0x75, 0x03,  //     Report Size (3)
    0x81, 0x03,  //     Input (Constant)

    // X/Y position (2 bytes)
    0x05, 0x01,  //     Usage Page (Generic Desktop)
    0x09, 0x30,  //     Usage (X)
    0x09, 0x31,  //     Usage (Y)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x95, 0x02,  //     Report Count (2)
    0x75, 0x08,  //     Report Size (8)
    0x81, 0x06,  //     Input (Data, Variable, Relative)

    // Vertical wheel (1 byte)
    0x09, 0x38,  //     Usage (Wheel)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x95, 0x01,  //     Report Count (1)
    0x75, 0x08,  //     Report Size (8)
    0x81, 0x06,  //     Input (Data, Variable, Relative)
    // Horizontal wheel (1 byte)
    0x05, 0x0C,        //     Usage Page (Consumer)
    0x0A, 0x38, 0x02,  //     Usage (AC Pan)
    0x15, 0x81,        //     Logical Minimum (-127)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x08,        //     Report Size (8)
    0x81, 0x06,        //     Input (Data, Variable, Relative)
    0xC0,              //   End Collection
    0xC0,              // End Collection
#    endif

#    ifdef EXTRAKEY_ENABLE
    // Extrakeys report descriptor
    0x05, 0x01,              // Usage Page (Generic Desktop)
    0x09, 0x80,              // Usage (System Control)
    0xA1, 0x01,              // Collection (Application)
    0x85, REPORT_ID_SYSTEM,  //   Report ID
    0x19, 0x01,              //   Usage Minimum (Pointer)
    0x2A, 0xB7, 0x00,        //   Usage Maximum (System Display LCD Autoscale)
    0x15, 0x01,              //   Logical Minimum
    0x26, 0xB7, 0x00,        //   Logical Maximum
    0x95, 0x01,              //   Report Count (1)
    0x75, 0x10,              //   Report Size (16)
    0x81, 0x00,              //   Input (Data, Array, Absolute)
    0xC0,                    // End Collection

    0x05, 0x0C,                // Usage Page (Consumer)
    0x09, 0x01,                // Usage (Consumer Control)
    0xA1, 0x01,                // Collection (Application)
    0x85, REPORT_ID_CONSUMER,  //   Report ID
    0x19, 0x01,                //   Usage Minimum (Consumer Control)
    0x2A, 0xA0, 0x02,          //   Usage Maximum (AC Desktop Show All Applications)
    0x15, 0x01,                //   Logical Minimum
    0x26, 0xA0, 0x02,          //   Logical Maximum
    0x95, 0x01,                //   Report Count (1)
    0x75, 0x10,                //   Report Size (16)
    0x81, 0x00,                //   Input (Data, Array, Absolute)
    0xC0                       // End Collection
#    endif
};
#endif

#if defined(CONSOLE_ENABLE)
const PROGMEM uchar console_hid_report[] = {
    0x06, 0x31, 0xFF,  // Usage Page (Vendor Defined - PJRC Teensy compatible)
    0x09, 0x74,        // Usage (Vendor Defined - PJRC Teensy compatible)
    0xA1, 0x01,        // Collection (Application)
    // Data to host
    0x09, 0x75,                 //   Usage (Vendor Defined)
    0x15, 0x00,                 //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,           //   Logical Maximum (0x00FF)
    0x95, CONSOLE_BUFFER_SIZE,  //   Report Count
    0x75, 0x08,                 //   Report Size (8)
    0x81, 0x02,                 //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x76,                 //   Usage (Vendor Defined)
    0x15, 0x00,                 //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,           //   Logical Maximum (0x00FF)
    0x95, CONSOLE_BUFFER_SIZE,  //   Report Count
    0x75, 0x08,                 //   Report Size (8)
    0x91, 0x02,                 //   Output (Data)
    0xC0                        // End Collection
};
#endif

#ifndef SERIAL_NUMBER
#    define SERIAL_NUMBER 0
#endif

#ifndef USB_MAX_POWER_CONSUMPTION
#    define USB_MAX_POWER_CONSUMPTION 500
#endif

// TODO: change this to 10ms to match LUFA
#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 1
#endif

// clang-format off
const PROGMEM usbStringDescriptor_t usbStringDescriptorZero = {
    .header = {
        .bLength         = USB_STRING_LEN(1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = {0x0409} // US English
};

const PROGMEM usbStringDescriptor_t usbStringDescriptorManufacturer = {
    .header = {
        .bLength         = USB_STRING_LEN(sizeof(STR(MANUFACTURER)) - 1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = LSTR(MANUFACTURER)
};

const PROGMEM usbStringDescriptor_t usbStringDescriptorProduct = {
    .header = {
        .bLength         = USB_STRING_LEN(sizeof(STR(PRODUCT)) - 1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = LSTR(PRODUCT)
};

const PROGMEM usbStringDescriptor_t usbStringDescriptorSerial = {
    .header = {
        .bLength         = USB_STRING_LEN(sizeof(STR(SERIAL_NUMBER)) - 1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = LSTR(SERIAL_NUMBER)
};

/*
 * Device descriptor
 */
const PROGMEM usbDeviceDescriptor_t usbDeviceDescriptor = {
    .header = {
        .bLength         = sizeof(usbDeviceDescriptor_t),
        .bDescriptorType = USBDESCR_DEVICE
    },
    .bcdUSB              = 0x0110,
    .bDeviceClass        = 0x00,
    .bDeviceSubClass     = 0x00,
    .bDeviceProtocol     = 0x00,
    .bMaxPacketSize0     = 8,
    .idVendor            = VENDOR_ID,
    .idProduct           = PRODUCT_ID,
    .bcdDevice           = DEVICE_VER,
    .iManufacturer       = 0x01,
    .iProduct            = 0x02,
    .iSerialNumber       = 0x03,
    .bNumConfigurations  = 1
};

/*
 * Configuration descriptors
 */
const PROGMEM usbConfigurationDescriptor_t usbConfigurationDescriptor = {
    .header = {
        .header = {
            .bLength         = sizeof(usbConfigurationDescriptorHeader_t),
            .bDescriptorType = USBDESCR_CONFIG
        },
        .wTotalLength        = sizeof(usbConfigurationDescriptor_t),
        .bNumInterfaces      = TOTAL_INTERFACES,
        .bConfigurationValue = 0x01,
        .iConfiguration      = 0x00,
        .bmAttributes        = (1 << 7) | USBATTR_REMOTEWAKE,
        .bMaxPower           = USB_MAX_POWER_CONSUMPTION / 2
    },

    /*
     * Keyboard
     */
    .keyboardInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = KEYBOARD_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 1,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x01,
        .bInterfaceProtocol  = 0x01,
        .iInterface          = 0x00
    },
    .keyboardHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0101,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(keyboard_hid_report)
    },
    .keyboardINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | 1),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = 8,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },

#    if defined(RAW_ENABLE)
    /*
     * RAW HID
     */
    .rawInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = RAW_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 2,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x00,
        .bInterfaceProtocol  = 0x00,
        .iInterface          = 0x00
    },
    .rawHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0101,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 2,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(raw_hid_report)
    },
    .rawINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = RAW_EPSIZE,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
    .rawOUTEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_HOST_TO_DEVICE | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = RAW_EPSIZE,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
#    endif
#    if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
    /*
     * Mouse/Extrakeys
     */
    .mouseExtraInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = MOUSE_EXTRA_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 1,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x00,
        .bInterfaceProtocol  = 0x00,
        .iInterface          = 0x00
    },
    .mouseExtraHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0101,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(mouse_extra_hid_report)
    },
    .mouseExtraINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = 8,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
#    endif
#    if defined(CONSOLE_ENABLE)
    /*
     * Console
     */
    .consoleInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = CONSOLE_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 2,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x00,
        .bInterfaceProtocol  = 0x00,
        .iInterface          = 0x00
    },
    .consoleHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0111,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(console_hid_report)
    },
    .consoleINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = CONSOLE_EPSIZE,
        .bInterval           = 0x01
    },
    .consoleOUTEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_HOST_TO_DEVICE | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = CONSOLE_EPSIZE,
        .bInterval           = 0x01
    },
#    endif
};

// clang-format on

USB_PUBLIC usbMsgLen_t usbFunctionDescriptor(struct usbRequest *rq) {
    usbMsgLen_t len = 0;

    /*
        debug("usbFunctionDescriptor: ");
        debug_hex(rq->bmRequestType); debug(" ");
        debug_hex(rq->bRequest); debug(" ");
        debug_hex16(rq->wValue.word); debug(" ");
        debug_hex16(rq->wIndex.word); debug(" ");
        debug_hex16(rq->wLength.word); debug("\n");
    */
    switch (rq->wValue.bytes[1]) {
        case USBDESCR_DEVICE:
            usbMsgPtr = (usbMsgPtr_t)&usbDeviceDescriptor;
            len       = sizeof(usbDeviceDescriptor_t);
            break;
        case USBDESCR_CONFIG:
            usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor;
            len       = sizeof(usbConfigurationDescriptor_t);
            break;
        case USBDESCR_STRING:
            switch (rq->wValue.bytes[0]) {
                case 0:
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorZero;
                    len       = usbStringDescriptorZero.header.bLength;
                    break;
                case 1:  // iManufacturer
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorManufacturer;
                    len       = usbStringDescriptorManufacturer.header.bLength;
                    break;
                case 2:  // iProduct
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorProduct;
                    len       = usbStringDescriptorProduct.header.bLength;
                    break;
                case 3:  // iSerialNumber
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorSerial;
                    len       = usbStringDescriptorSerial.header.bLength;
                    break;
            }
            break;
        case USBDESCR_HID:
            switch (rq->wValue.bytes[0]) {
                case KEYBOARD_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.keyboardHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#if defined(RAW_ENABLE)
                case RAW_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.rawHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif
#if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
                case MOUSE_EXTRA_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.mouseExtraHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif
#if defined(CONSOLE_ENABLE)
                case CONSOLE_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.consoleHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif
            }
            break;
        case USBDESCR_HID_REPORT:
            /* interface index */
            switch (rq->wIndex.word) {
                case KEYBOARD_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)keyboard_hid_report;
                    len       = sizeof(keyboard_hid_report);
                    break;
#if defined(RAW_ENABLE)
                case RAW_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)raw_hid_report;
                    len       = sizeof(raw_hid_report);
                    break;
#endif
#if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
                case MOUSE_EXTRA_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)mouse_extra_hid_report;
                    len       = sizeof(mouse_extra_hid_report);
                    break;
#endif
#if defined(CONSOLE_ENABLE)
                case CONSOLE_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)console_hid_report;
                    len       = sizeof(console_hid_report);
                    break;
#endif
            }
            break;
    }
    // debug("desc len: "); debug_hex(len); debug("\n");
    return len;
}
