/**
 * [Fat Bottomed Board] controller firmware
 * 
 * @author  Ben
 */

// System includes
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TFT.h>
#include <MD_REncoder.h>

// Project includes
#include "defines.h"
#include "display.h"
#include "data.h"
// Machine state pages
#include "stateMain.h"
#include "stateMenu.h"
#include "stateMacro.h"
#include "stateSetup.h"
#include "stateBacklight.h"
#include "gamepong.h"

// Project objects
TFT         
    display = TFT(LCD_CS, LCD_DC, LCD_RESET);                           // TFT display
File
    fileMacro;                                                          // MACRO.KEY file
MD_REncoder
    control = MD_REncoder(ENCODER_CONTROL_CLK, ENCODER_CONTROL_DT),     // [control] Rotary encoder
    macro   = MD_REncoder(ENCODER_MACRO_CLK,   ENCODER_MACRO_DT);       // [macro]   Rotary encoder
menuObject                                                              
    menu;                                                               // menu application widget
gaugeObject
    gauge;                                                              // gauge application widget
byte
    status,                                                             // State Machine status
    keyboardLeds,                                                       // Current keyboard leds status
    ledMode, ledLight,                                                  // Backlight leds (Light Mode, Light intensity)
    AudioVolume,                                                        // Current audio volume (percentage)
    screenSaver,                                                        // Screen inactivity timeout (1 x 10s)
    controlScroll;                                                      // Lines to scroll
unsigned long                                                           // UL? a total waste of space but millis() might use that
    delayScrollArrow,                                                   // Scroll arrow delay on screen (ms) on main scroll
    delayKeyboardStatus,                                                // Delay led status detect (num, caps)
    inactivity;                                                         // Inactivity time, used in conjunction with [screenSaver]. 0:Screen turned off
char
    sCompose[3],                                                        // Current Keyboard : "UI", "IT", "EN"
    sOSType[10],                                                        // Current OS       : "Linux", "MacOS", "Windows"
    cmdBuffer[BUFFERMAX],
    cmdBuffer1[BUFFERTEENSY];


// Change state machine state
void stateSet(byte newStatus) {
    status = newStatus;
    switch (status) {
    case STATUS_NONE:
        mainPage();
        keyboardLeds = 0xFF;
        return;
    case STATUS_MENU:
        menuPage();
        return;
    case STATUS_SETUP:
        setupPage();
        return;
    case STATUS_BACKLIGHT:
        backlightPage();
        return;
    case STATUS_GAUGE:
        gauge.Show();
        return;
    case STATUS_MACRO:
        macroPage();
        return;
    case STATUS_REMOTECONFIG:
        displayRemoteConfigWaiting();
        return;
    case STATUS_GAME_PONG:
        gamepongPage();
    }
} /**/


// Return current status
byte stateGet() {
    return status;
} /**/


// Show controls or changing widgets in the current state
void stateLoop() {
    // Screensaver detection                                                    // ([screenSaver] * 10s)
    if ((millis()-inactivity)/1000 > screenSaver*10) {
        inactivity = 0;                                                         // inactivity is 0 when display is turned off
        displayLed(LOW);
    }
    if (inactivity > 0) {
        // Menus loop operations, if any
        switch (status) {
        case STATUS_NONE:
            mainLoop();                                                         // Main menu display (Num,Caps and scroll arrows)
            delay(5);                                                           // Some delay so the mouse doesn't move too fast
            break;
        case STATUS_GAME_PONG:
            gamepongLoop();
            break;
        }
    }
} /**/


// Detected action, tell program what to do
void stateAction(byte Action) {
    // Drop NULL actions
    if (Action==ACTION_NONE)
        return;
    // if I received some input and screen is now turned off I need to turn it on again
    if (inactivity==0) {
        displayLed(HIGH);
    }
    inactivity = millis();
    // Now detect proper action
    switch (status) {
    case STATUS_NONE:
        mainAction(Action);
        break;
    case STATUS_MENU:
        menuAction(Action);
        break;
    case STATUS_SETUP:
        setupAction(Action);
        break;
    case STATUS_BACKLIGHT:
        backlightAction(Action);
        break;
    case STATUS_GAUGE:
        gauge.action(Action);
        break;
    case STATUS_MACRO:
        macroAction(Action);
        break;
    case STATUS_GAME_PONG:
        gamepongAction(Action);
        break;
    }
} /**/


/**
 * LED MODE SET - Setup led backlight (based on [ledMode] and [ledLight])
 */
void ledModeSet() {
    // General backlight leds
    switch (ledMode) {
    case LED_MODE_ON:
    case LED_MODE_ON_MORELIGHT:
    case LED_MODE_REVERSE:
        analogWrite(PIN_LED_GENERAL, ledLight);
        break;    
    default:
        analogWrite(PIN_LED_GENERAL, 0);
        break;
    }
} /**/


/**
 * @see Internally used by [ledCapsLockSet] [ledNumLockSet]
 */
void ledServiceSet(byte Active, byte LedPin) {
    switch (ledMode) {
    case LED_MODE_OFF:
        analogWrite(LedPin, 0);
        return;
    case LED_MODE_ON:
        analogWrite(LedPin, ledLight);
        return;
    case LED_MODE_ON_MORELIGHT:
        if (Active == LOW) {
            analogWrite(LedPin, ledLight);
        } else {
            analogWrite(LedPin, ledLight*2);
        }
        return;
    case LED_MODE_NORMAL:
        if (Active == LOW) {
            analogWrite(LedPin, 0);
        } else {
            analogWrite(LedPin, ledLight);
        }
        return;
    case LED_MODE_REVERSE:
        if (Active == LOW) {
            analogWrite(LedPin, ledLight);
        } else {
            analogWrite(LedPin, 0);
        }
        return;
    }
} /**/


/**
 * SET CAPS LOCK
 */
void ledCapsLockSet(byte Active) {
    ledServiceSet(Active, PIN_LED_CAPS_LOCK);
} /**/


/**
 * SET NUM LOCK
 */
void ledNumLockSet(byte Active) {
    ledServiceSet(Active, PIN_LED_NUM_LOCK);
} /**/


/**
 * Set required layout (on TFT display)
 */
void layout(const char *Layout) {
    memcpy(sCompose, Layout, 2);
    sCompose[2] = 0x00;
    mainCompose();
} /**/


/**
 * Show current OS (just a label sent from qmk fw)
 */
void osType(char *osType) {
    // memcpy(sOSType, osType, strlen(osType));
    // sOSType[strlen(osType)] = 0x00;
    display.fillRect(0, 0, 55, 10, 0x0000);
    display.setTextSize(1);
    display.stroke(255, 255, 255);
    display.setCursor(1, 1);
    // display.print(sOSType);
    display.print(osType);
} /**/


// Init
void setup() {
    // TFT init
    pinMode(LCD_LED, OUTPUT);                       // Set LCD_LED as output
    delay(500);
    displayLed(HIGH);                               // Turn on lcd led display
    delay(500);
    display.begin();                                // TFT begin() more times ? yes, if you put it once it doesn't init the screen 
    delay(250);                                     // .... properly on boot. Do it more than once to properly boot on dry run
    display.begin();
    delay(250);
    delayKeyboardStatus =
    delayScrollArrow    = 0;
    inactivity = millis();
    Mouse.begin();                                  // HID Mouse setup, keyboard.begin is not needed
    cmdStart();
    Serial.begin(115200);                           // Serial HID (CDC) used for the keyboard setup from host
    // while (!Serial);                                // Wait for serial port to connect. Needed for native USB
    cmdInitTeensy();
    Serial1.begin(9600);
    // Encoders setup
    control.begin();
    macro.begin();
    pinMode(ENCODER_CONTROL_SW, INPUT_PULLUP);
    pinMode(ENCODER_MACRO_SW,   INPUT_PULLUP);
    // SD test (begin)
    if (!SD.begin(SD_CS)) {
        displayErrorMessage(F(" open failed"));
        while (1);
    }
    fileMacro = SD.open(FILE_MACRO, FILE_WRITE);
    if (!fileMacro) {
        displayErrorMessage(F("  MACRO.KEY"));
        while (1);
    }
    fileMacro.close();
    // Database readings
    controlScroll = configRead(DB_SCROLL_SIZE,  1);
    AudioVolume   = configRead(DB_AUDIO,        50);
    screenSaver   = configRead(DB_SCREEN_SAVER, 30);// Default: 5mins ([30] x 10s)
    ledMode       = configRead(DB_LED_MODE,     LED_MODE_NORMAL);
    ledLight      = configRead(DB_LED_LIGHT,    2);
    ledModeSet();
    // Menu
    memset(sCompose, 0x00, 3); memcpy_P(sCompose, F("UI"),     2);
    memset(sOSType,  0x00, 6); memcpy_P(sOSType,  F("Linux"),  5);
    stateSet(STATUS_NONE);
} /**/


// Main - loop
void loop() {
    // encoder [Control] movement
    switch (control.read()) {
        case DIR_CW:
            stateAction(ACTION_CONTROL_RIGHT);
            break;
        case DIR_CCW:
            stateAction(ACTION_CONTROL_LEFT);
            break;
    }
    // encoder [Control] button toggle
    if (digitalRead(ENCODER_CONTROL_SW) == LOW) {
        stateAction(ACTION_CONTROL_BUTTON);
    }

    // encoder [Macro] movement
    switch (macro.read()) {
        case DIR_CW:
            stateAction(ACTION_MACRO_RIGHT);
            break;
        case DIR_CCW:
            stateAction(ACTION_MACRO_LEFT);
            break;
    }
    // encoder [Macro] button toggle
    if (digitalRead(ENCODER_MACRO_SW) == LOW) {
        stateAction(ACTION_MACRO_BUTTON);
    }

    // Check if there some data from Host
    if (Serial.available() > 0) {
        cmdSerialRead();                        // read the incoming byte and process it [data.cpp]
    }
    // ...or from the other Teensy board
    if (Serial1.available() > 0) {
        cmdSerial1Read();
    }
    
    // State machine loop
    stateLoop();
} /**/
