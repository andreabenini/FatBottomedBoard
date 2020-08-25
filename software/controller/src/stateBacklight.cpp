#include "stateBacklight.h"
extern menuObject   menu;
extern gaugeObject  gauge;
extern byte         ledMode;
extern byte         ledLight;
extern byte         keyboardLeds;


/**
 * display page title and menu
 */
void backlightPage() {
    menuInit(F("BACKLIGHT"), 25, backlightShow);
} /**/


/**
 * display setup menu, right after [setupPage]
 */
void backlightShow() {
    char text[30];
    switch (ledMode) {
    case LED_MODE_OFF:
        menu.itemShow(F("Mode:          Always OFF"));
        break;
    case LED_MODE_NORMAL:
        menu.itemShow(F("Mode:            Standard"));
        break;
    case LED_MODE_ON:
        menu.itemShow(F("Mode:           Always ON"));
        break;
    case LED_MODE_ON_MORELIGHT:
        menu.itemShow(F("Mode:     ON + Light Diff"));
        break;
    case LED_MODE_REVERSE:
        menu.itemShow( F("Mode:            Reversed"));
        break;
    }
    sprintf_P(text, PSTR("LED Brightness       [%2d]"), ledLight);
    menu.itemShowStr(text);
    menu.itemShow(F("EXIT"));
} /**/


void backlightAction(byte Action) {
    switch (Action) {
    case ACTION_CONTROL_LEFT:       // Control rotary encoder movement [UP]
        menu.moveUp();
        break;
    case ACTION_CONTROL_RIGHT:      // Control rotary encoder movement [DOWN]
        menu.moveDown();
        break;
    case ACTION_CONTROL_BUTTON:     // Control button press
        backlightSelect(menu.itemGet());
        break;
    }
} /**/


void backlightSelect(byte Choice) {
    switch (Choice) {
    case 0:                         // Change backlight mode
        ledMode = (ledMode==LED_MODE_REVERSE? 0: ledMode+1);
        configWrite(DB_LED_MODE, ledMode);
        menu.showMenu();
        ledModeSet();
        ledCapsLockSet(keyboardLeds & LED_CAPS_LOCK ? HIGH: LOW);
        ledNumLockSet(keyboardLeds  & LED_NUM_LOCK  ? HIGH: LOW);
        delay(500);
        break;
    case 1:                         // Change LED brightness
        gauge.handler(backlightControl);
        analogWrite(PIN_LED_GENERAL, ledLight);
        gauge.init(&ledLight, DB_LED_LIGHT, 0, 20, 1, F("brightness"), F("LED backlight intensity"));
        delay(500);
        ledModeSet();
        ledCapsLockSet(keyboardLeds & LED_CAPS_LOCK ? HIGH: LOW);
        ledNumLockSet(keyboardLeds  & LED_NUM_LOCK  ? HIGH: LOW);
        break;
    default:                        // Return to default state
        stateSet(STATUS_MENU);
    }
} /**/


/**
 * VOLUME CONTROL - Volume control with rotary encoder (because everyone love knobs !)
 */
void backlightControl(byte Action) {
    switch (Action) {
    case GAUGE_UP:
    case GAUGE_DOWN:
        analogWrite(PIN_LED_GENERAL, gauge.Value());
        break;
    }
} /**/
