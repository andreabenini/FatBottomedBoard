#include <main.h>
#include <general.h>

/**
 * LED ON - Turn Led on
 */
void LedOn() {
    PORTC &= ~(1<< (IO_PORT_C ^ IO_PORT_C5) );
} /**/


/**
 * LED OFF - Turn Led off
 */
void LedOff() {
    PORTC |= 1 << (IO_PORT_C ^ IO_PORT_C5) ;
} /**/


/**
 * LED BLINK - Make 1 blink with the led (
 */
void LedBlink() {
    LedOn();
    DelayMSec(BLINK_DELAY);
    LedOff();
    DelayMSec(BLINK_DELAY);
} /**/


/**
 * DELAY MSEC - Delays the process with a sleep of X ms
 * @param  iMilliSeconds (unsigned int) - Time to delay (in milliseconds of course)
 * @return (void)
 *
 * @see    _delay_ms uses a floating point datatype if you call that function in many
 *         places in your code then it becomes very fat. An integer is enough
 */
void DelayMSec(unsigned short int iMilliSeconds) {
    while (iMilliSeconds--) {
        _delay_ms(0.96);
        wdt_reset();
    }
} /**/


/**
 * SET ERROR - Shows an error with a blinking led, it blinks the Error number
 * @param  iError (uint8_t) Number of blinks for the error
 * @return (void)
 */
void SetError(uint8_t iError) {
    uint8_t i;
    while (1) {
        for (i=iError; i>0; i--) {
            LedBlink();
        }
        DelayMSec(BLINK_DELAY*4);
    }
} /**/


/**
 * SERIAL INIT - Open the serial port with the specified setup
 * @param  iSerialComSetup (unsigned short int) predefined setup for com port (see COM.H)
 * @return (int)       TRUE/FALSE on OK/ERROR
 */
void SerialInit() {
	unsigned int iBitTimer;
	iBitTimer = (F_CPU / 1200 / 16) -1;			// iBitTimer set to baud prescaler
	UBRR0H = (unsigned char) (iBitTimer >> 8);	// Set the baud rate
	UBRR0L = (unsigned char) iBitTimer;
	UCSR0C = (3 << UCSZ00);						// Framing to 8N1
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);		// Init bits for the serial port (init as a serial port)

    UCSR0B |= (1 << RXCIE0);                    // Enable the USART Recieve Complete interrupt (USART_RXC)
} /**/

