#include "stateMenu.h"
extern byte         AudioVolume;
extern menuObject   menu;
extern gaugeObject  gauge;


/**
 * display page title and menu
 */
void menuPage() {
    menuInit(F("MAIN MENU"), 30, menuShow);
} /**/


/**
 * display menu, right after [menuPage]
 */
void menuShow() {
    menu.itemShow(F("Audio Volume"));
    menu.itemShow(F("Led Backlight"));
    menu.itemShow(F("Keyboard Settings"));
    menu.itemShow(F("Mouse Reset"));
    menu.itemShow(F("Play Pong"));
    menu.itemShow(F("EXIT"));
} /**/


void menuAction(byte Action) {
    switch (Action) {
    case ACTION_CONTROL_LEFT:       // Control rotary encoder movement [UP]
        menu.moveUp();
        break;
    case ACTION_CONTROL_RIGHT:      // Control rotary encoder movement [DOWN]
        menu.moveDown();
        break;
    case ACTION_CONTROL_BUTTON:     // Control button press
        menuSelect(menu.itemGet());
        break;
    }
} /**/


void menuSelect(byte Choice) {
    switch (Choice) {
    case 0:                         // Audio Volume
        gauge.handler(VolumeControl);
        gauge.init(&AudioVolume, DB_AUDIO, 0, 100, 6, F("%"), F("AUDIO VOLUME"));
        break;
    case 1:                         // LED Backlight // TODO: Backlight LED
        break;
    case 2:                         // Keyboard Settings
        stateSet(STATUS_SETUP);
        break;
    case 3:                         // Mouse Reset
        Mouse.end();
        displayClear();
        delay(1000);
        Mouse.begin();
        delay(500);
        stateSet(STATUS_NONE);
        break;
    case 4:
        stateSet(STATUS_GAME_PONG);
        break;
    default:                        // Return to default state
        stateSet(STATUS_NONE);
    }
} /**/


/**
 * VOLUME CONTROL - Volume control with rotary encoder (because everyone love knobs !)
 */
void VolumeControl(byte Action) {
    switch (Action) {
    case GAUGE_UP:
        Keyboard.press(KEY_MEDIA_VOLUME_DEC);
        delay(100);
        Keyboard.release(KEY_MEDIA_VOLUME_DEC);
        break;
    case GAUGE_DOWN:
        Keyboard.press(KEY_MEDIA_VOLUME_INC);
        delay(100);
        Keyboard.release(KEY_MEDIA_VOLUME_INC);
        break;
    }
} /**/
