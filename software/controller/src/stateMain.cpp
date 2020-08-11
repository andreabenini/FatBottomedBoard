#include <usb_private.h>
#include "stateMain.h"
extern unsigned int delayKeyboardStatus;
extern unsigned int delayScrollArrow;
extern byte         controlScroll;
extern byte         keyboardLeds;
extern TFT          display;
extern char         sCompose[3];

#define SCROLL_UP(color)    display.fillTriangle(20, 40, 140, 40, 80, 10,  color)
#define SCROLL_DOWN(color)  display.fillTriangle(20, 80, 140, 80, 80, 110, color)
#define LED_NUM_LOCK        0b01
#define LED_CAPS_LOCK       0b10


/**
 * Show main page controls after changing the state
 */
void mainPage() {
    display.background(0, 0, 0);              // Clear the screen, black background
    display.stroke(255, 255, 255);
    display.setTextSize(1);
    display.setCursor(132, 108);
    display.print(F("PUSH"));
    display.setCursor(115, 118);
    display.print(F("to menu"));
    mainCompose();
    osType("Linux");
} /**/


/**
 * Do something with the current action
 */
void mainAction(byte Action) {
    switch (Action) {
        case ACTION_CONTROL_LEFT:       // Rotary encoder movement [UP]
            SCROLL_UP(0xFA04);
            Mouse.scroll(controlScroll);
            delayScrollArrow = millis();
            break;
        case ACTION_CONTROL_RIGHT:      // Rotary encoder movement [DOWN]
            SCROLL_DOWN(0xFA04);
            Mouse.scroll(-controlScroll);
            delayScrollArrow = millis();
            break;
        case ACTION_CONTROL_BUTTON:     // Button press
            stateSet(STATUS_MENU);
            break;
        case ACTION_MACRO_LEFT:         // Macro mode menu
        case ACTION_MACRO_RIGHT:
        case ACTION_MACRO_BUTTON:
            stateSet(STATUS_MACRO);
            break;
    }
} /**/


/**
 * Show widgets on each loop. Detect keyboard [NumLock] and [CapsLock]
 */
void mainLoop() {
    // get keyboard status every 1s
    if (millis()-delayKeyboardStatus > 1000) {
        delayKeyboardStatus = millis();
        if (keyboardLeds != keyboard_leds) {
            keyboardLeds = keyboard_leds;                   // 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
            mainCapsLock(keyboardLeds & LED_CAPS_LOCK ? HIGH: LOW);
            mainNumLock(keyboardLeds  & LED_NUM_LOCK  ? HIGH: LOW);
        }
    }
    // delete scroll arrows after 1s
    if ((delayScrollArrow > 0) && (millis()-delayScrollArrow > 1000)) {
        delayScrollArrow = 0;
        SCROLL_UP(0x0000);
        SCROLL_DOWN(0x0000);
    }
} /**/


void mainCompose() {
    display.setTextSize(1);
    display.fillRect(122, 0, 37, 28, 0xFFFF);
    display.stroke(0, 0, 0);
    display.setCursor(123, 1);    
    display.print(F("layout"));
    display.fillRect(123, 10, 35, 17, 0x0000);
    display.stroke(255, 255, 255);
    display.setTextSize(2);
    display.setCursor(129, 12);   
    display.print(sCompose);
} /**/


void mainNumLock(byte Active) {
    display.setTextSize(2);
    display.fillRect(20, 48, 58, 25, 0x07FF);
    if (Active==LOW) {
        display.fillRect(21, 49, 56, 23, 0x0000);
        display.setCursor(32, 54);
        display.print(F("NUM"));
    } else {
        display.stroke(0, 0, 0);
        display.setCursor(32, 54);
        display.print(F("NUM"));
        display.stroke(255, 255, 255);
    }
    ledNumLockSet(Active);
} /**/


void mainCapsLock(byte Active) {
    display.setTextSize(2);
    display.fillRect(82, 48, 58, 25, 0x07FF);
    if (Active==LOW) {
        display.fillRect(83, 49, 56, 23, 0x0000);
        display.setCursor(88, 54);
        display.print(F("CAPS"));
    } else {
        display.stroke(0, 0, 0);
        display.setCursor(88, 54);
        display.print(F("CAPS"));
        display.stroke(255, 255, 255);
    }
    ledCapsLockSet(Active);
} /**/
