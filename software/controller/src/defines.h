/**
 * Project defines
 */
#ifndef DEFINES_H
#define DEFINES_H

// SD
#define SD_CS                       24
#define FILE_MACRO                  "MACRO.KEY"
// LCD
#define LCD_LED                     A4
#define LCD_DC                      A5
#define LCD_RESET                   A6
#define LCD_CS                      A7
#define FONT1_MAXCOLS               25
#define LCD_WIDTH                   160
#define LCD_HEIGHT                  128
// LED Backlight
#define PIN_LED_GENERAL             27      // PB7  (PWM)
#define PIN_LED_CAPS_LOCK           0       // PD0  (PWM)
#define PIN_LED_NUM_LOCK            1       // PD1  (PWM)
#define LED_MODE_OFF                0
#define LED_MODE_NORMAL             1
#define LED_MODE_ON                 2
#define LED_MODE_ON_MORELIGHT       3
#define LED_MODE_REVERSE            4
// Encoders
#define ENCODER_CONTROL_SW          8
#define ENCODER_CONTROL_DT          9
#define ENCODER_CONTROL_CLK         10
#define ENCODER_MACRO_SW            11
#define ENCODER_MACRO_DT            12
#define ENCODER_MACRO_CLK           13
// State machine
#define STATUS_NONE                 0b0000
#define STATUS_MENU                 0b0001
#define STATUS_SETUP                0b0010
#define STATUS_GAUGE                0b0011
#define STATUS_MACRO                0b0100
#define STATUS_REMOTECONFIG         0b0101
#define STATUS_GAME_PONG            0b1000
// Actions
#define ACTION_NONE                 0b0000
#define ACTION_CONTROL_LEFT         0b0001
#define ACTION_CONTROL_RIGHT        0b0010
#define ACTION_CONTROL_BUTTON       0b0011
#define ACTION_MACRO_LEFT           0b0101
#define ACTION_MACRO_RIGHT          0b0110
#define ACTION_MACRO_BUTTON         0b0111
#define GAUGE_DOWN                  0b00
#define GAUGE_UP                    0b01
// EEPROM addresses for settings
#define DB_SCROLL_SIZE              0x00
#define DB_SCREEN_SAVER             0x01
#define DB_AUDIO                    0x02
#define DB_LED_MODE                 0x03
#define DB_LED_LIGHT                0x04
// PC Configuration actions
#define DATAMODE_NONE               0b00
#define DATAMODE_MACRO              0b01
#define BUFFERMAX                   256
#define BUFFERTEENSY                20
// Macro related defines
#define MACROBUFFER_SIZE            1024


// Project function defines
#define displayLed(Active)                      digitalWrite(LCD_LED,Active)
#define menuInit(Title, TitleX, DisplayFun)     menu.init(Title, TitleX, 1, 0, 0, 7, 5, 20, 16, DisplayFun)

#endif
