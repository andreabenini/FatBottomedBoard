#include "stateSetup.h"
extern menuObject   menu;
extern gaugeObject  gauge;
extern byte         screenSaver;
extern byte         controlScroll;


/**
 * display page title and menu
 */
void setupPage() {
    menuInit(F("SETUP"), 50, setupShow);
} /**/


/**
 * display setup menu, right after [setupPage]
 */
void setupShow() {
    char text[30];
    sprintf_P(text, PSTR("Scroll Size          %3dL"), controlScroll);
    menu.itemShowStr(text);
    sprintf_P(text, PSTR("Screen saver    (%3dx10s)"), screenSaver);
    menu.itemShowStr(text);
    menu.itemShow(F("Firmware Upgrade"));
    menu.itemShow(F("Reboot"));
    menu.itemShow(F("EXIT"));
} /**/


void setupAction(byte Action) {
    switch (Action) {
    case ACTION_CONTROL_LEFT:       // Control rotary encoder movement [UP]
        menu.moveUp();
        break;
    case ACTION_CONTROL_RIGHT:      // Control rotary encoder movement [DOWN]
        menu.moveDown();
        break;
    case ACTION_CONTROL_BUTTON:     // Control button press
        setupSelect(menu.itemGet());
        break;
    }
} /**/


void setupSelect(byte Choice) {
    switch (Choice) {
    case 0:                         // Mouse scroll size
        gauge.init(&controlScroll, DB_SCROLL_SIZE,  1,  10, 1, F("steps"), F("LINES TO SCROLL"));
        break;
    case 1:                         // Inactivity: screen saver
        gauge.init(&screenSaver,   DB_SCREEN_SAVER, 0, 100, 1, F("x 10s"), F("Inactivity (screen saver)"));
        break;
    case 2:                         // Firmware upgrade
        displayRemoteConfigWaiting();
        cli();
        // disable watchdog, if enabled as well as all peripherals
        UDCON = 1;
        USBCON = (1<<FRZCLK);       // disable USB
        UCSR1B = 0;
        delay(50);                  // wait for a while to init the USB in bootloader mode
        // init everything and go to bootloader mode
        EIMSK   = 0;    PCICR   = 0;    SPCR    = 0;    ACSR    = 0;    EECR    = 0;    ADCSRA  = 0;
        TIMSK0  = 0;    TIMSK1  = 0;    TIMSK2  = 0;    TIMSK3  = 0;    UCSR1B  = 0;    TWCR    = 0;
        DDRA    = 0;    DDRB    = 0;    DDRC    = 0;    DDRD    = 0;    DDRE    = 0;    DDRF    = 0;
        PORTA   = 0;    PORTB   = 0;    PORTC   = 0;    PORTD   = 0;    PORTE   = 0;    PORTF   = 0;
        asm volatile("jmp 0x1FC00");
        break;
    case 3:                         // Program reboot
        displayRemoteConfigWaiting();
        asm volatile("jmp 0");
        break;
    default:                        // Return to default state
        stateSet(STATUS_MENU);
    }
} /**/
