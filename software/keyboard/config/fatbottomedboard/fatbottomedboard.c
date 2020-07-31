/* Copyright 2020 Ben
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "fatbottomedboard.h"

/**
 * Serial globals
 */
// These buffers may be any size from 2 to 256 bytes.
#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 40

static volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
static volatile uint8_t tx_buffer_head;
static volatile uint8_t tx_buffer_tail;
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_buffer_head;
static volatile uint8_t rx_buffer_tail;

// Current operating system (default: linux)
osType osCurrent;

/**/


// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/**
 * put your keyboard start-up code here, runs once when the firmware starts up
 */
void matrix_init_kb(void) {
    uart_init(9600);
    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    led_set_user(usb_led);
}


void layout(const char *str) {
    _delay_ms(100);
    uart_putchar('l');
    _delay_ms(20);
    uart_print_P_delay(str);
    uart_putchar('\n');
} /**/


/**
 * OS FUNCTIONS
 */
void osChange(osType osDefault) {
    osCurrent = osDefault;
}
void osToggle(void) {
    switch (osCurrent) {
    case LINUX:
        osChange(MACOS);
        break;
    case MACOS:
        osChange(WIN);
        break;
    case WIN:
    default:
        osChange(LINUX);
        break;
    }
} /**/
void osSend(void) {
    _delay_ms(100);
    uart_putchar('o');
    _delay_ms(20);
    switch (osCurrent) {
    case LINUX:
        uart_putchar('L');
        break;
    case MACOS:
        uart_putchar('M');
        break;
    case WIN:    
    default:
        uart_putchar('W');
        break;
    }
    _delay_ms(20);
    uart_putchar('\n');
    _delay_ms(20);
}


/**
 * SERIAL FUNCTIONS (communicate with the other teensy board)
 */

// Initialize the UART
void uart_init(uint32_t baud) {
    cli();
    UBRR1 = (F_CPU / 4 / baud - 1) / 2;
    UCSR1A = (1 << U2X1);
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
    tx_buffer_head = tx_buffer_tail = 0;
    rx_buffer_head = rx_buffer_tail = 0;
    sei();
} /**/

// Transmit a byte
void uart_putchar(uint8_t c) {
    uint8_t i;
    i = tx_buffer_head + 1;
    if (i >= TX_BUFFER_SIZE) {
        i = 0;
    }
    while (tx_buffer_tail == i) ; // wait until space in buffer
    //cli();
    tx_buffer[i] = c;
    tx_buffer_head = i;
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1) | (1 << UDRIE1);
    //sei();
} /**/

void uart_print_P(const char *str) {
    char c;
    while (1) {
        c = pgm_read_byte(str++);
        if (!c) {
            break;
        }
        uart_putchar(c);
    }
} /**/


void uart_print_P_delay(const char *str) {
    char c;
    while (1) {
        c = pgm_read_byte(str++);
        if (!c) {
            break;
        }
        uart_putchar(c);
        _delay_ms(20);
    }
} /**/


// Receive a byte
uint8_t uart_getchar(void) {
    uint8_t c, i;
    while (rx_buffer_head == rx_buffer_tail) ; // wait for character
    i = rx_buffer_tail + 1;
    if (i >= RX_BUFFER_SIZE) {
        i = 0;
    }
    c = rx_buffer[i];
    rx_buffer_tail = i;
    return c;
} /**/

// Return the number of bytes waiting in the receive buffer.
// Call this before uart_getchar() to check if it will need
// to wait for a byte to arrive.
uint8_t uart_available(void) {
    uint8_t head, tail;
    head = rx_buffer_head;
    tail = rx_buffer_tail;
    if (head >= tail) {
        return head - tail;
    }
    return RX_BUFFER_SIZE + head - tail;
} /**/

// Transmit Interrupt
ISR(USART1_UDRE_vect) {
    uint8_t i;
    if (tx_buffer_head == tx_buffer_tail) {
        // buffer is empty, disable transmit interrupt
        UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    } else {
        i = tx_buffer_tail + 1;
        if (i >= TX_BUFFER_SIZE) {
            i = 0;
        }
        UDR1 = tx_buffer[i];
        tx_buffer_tail = i;
    }
} /**/

// Receive Interrupt
ISR(USART1_RX_vect) {
    uint8_t c, i;
    c = UDR1;
    i = rx_buffer_head + 1;
    if (i >= RX_BUFFER_SIZE) {
        i = 0;
    }
    if (i != rx_buffer_tail) {
        rx_buffer[i] = c;
        rx_buffer_head = i;
    }
} /**/
