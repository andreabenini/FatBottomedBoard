#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  // sei()
#include <util/delay.h>     // _delay_ms()
#include <avr/eeprom.h>
#include <string.h>         // memcpy() and memory handling functions

#include <avr/pgmspace.h>   // required by usbdrv.h
#include "usbdrv.h"


// I/O Port defines
#define IO_PORT_C       0b00001000              // PortC on the CPU, I/O definition
#define IO_PORT_C5      0b00001101


// General defines
#define BLINK_DELAY     500                     // Blink delay for the led

