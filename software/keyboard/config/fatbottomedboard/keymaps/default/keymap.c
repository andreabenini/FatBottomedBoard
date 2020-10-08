/**
 * Copyright 2020 Ben
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
 * 
 */
#include QMK_KEYBOARD_H
    /**
     * [FatBottomedBoard Layout Template]      { 119 keymap, 20x6 }
     *
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |   Browser   |   | Esc  |      |  F1  |  F2  |  F3  |  F4  |    |  F5  |  F6  |  F7  |  F8  |   |  F9  |  F10 |  F11 |  F12 |     | Print|Switch| Play |     |   1  |   2  |   3  |   4  | 21
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    | Undo | Redo |   |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |   BackSpace   |     |Insert| Home | PgUp |     |BlkNum|   /  |   *  |   -  | 23
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    | Term | Code |   |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |     \      |     |Delete|  End | PgDn |     |   7  |   8  |   9  |      | 22
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|   +  |
     *    |  Cut | Open |   |  CapsLock  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |      Enter     |                                |   4  |   5  |   6  |      | 19
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    | Copy | Close|   |  Shift        |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |          Shift     |            |   ^  |            |   1  |   2  |   3  |      | 18
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|  Ent |
     *    | Paste| Save |   |  Ctrl  |  Alt   |  Cmd   |                S p a c e                  |   FN   |  AltG  |   Cmd  |  Ctrl  |     |   <  |   ¥  |   >  |     |   0         |   .  |      | 16
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     *
     *    - ROW -  1   2   3   4   5   6
     *      pin   C2  C3  C4  C5  C6  C7
     *
     *    - COL -  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
     *      pin   F2  F1  F0  E6  E7  B0  B1  B2  B3  B4  B5  B6  B7  D4  D5  D7  E0  E1  C0  C1
     */


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE_USA_,
    _BASE_ITA_,
    _BASE_USA_INTL_,
    _EXT_FN_,
    _EXT_PLAY_,
};


// Defines custom key codes
enum custom_keycodes {
    CHG_OS = SAFE_RANGE,
    EURO,       // €
    POUND,      // £
    SECT1,      //
    AGRAVE,     // à
    EGRAVE,     // è
    IGRAVE,     // ì
    OGRAVE,     // ò
    UGRAVE,     // ù
    AACUTE,     // á
    EACUTE,     // é
    IACUTE,     // í
    OACUTE,     // ó
    UACUTE      // ú
};


// Define useful macros
#define FKEY(value) LCTL(LSFT(LGUI(KC_##value)))// Remapping for custom function keys, to avoid collision "Shift+Control+Super+<yourKey>" is used
#define UNDO        LCTL(KC_Z)                  // KC_UNDO  seems the right choice but a lot of programs ignores it and direcly map UNDO to Ctrl+Z (vscode is one of them)
#define REDO1       LCTL(KC_Y)                  // KC_AGAIN same behavior of KC_UNDO but unfortunately there's no common choiche among programs    (vscode  uses CTRL+Y)
#define REDO2       LCTL(LSFT(KC_Z))            // KC_AGAIN                                                                                        (eclipse uses CTRL+SHIFT+Z)
#define BCUT1       LCTL(KC_X)                  // KC_CUT/COPY/PASTE follow same problems had above with KC_UNDO where most programs use them but someone doesn't (Terminal programs for example)
#define BCOPY1      LCTL(KC_C)                  // KC_CUT/COPY/PASTE
#define BPASTE1     LCTL(KC_V)                  // KC_CUT/COPY/PASTE
#define BCUT2       LSFT(KC_DEL)                // KC_CUT/COPY/PASTE same as above but some programs still use Ctrl+Ins, Shift+Ins, Shift+Canc (GIT Terminal under windows for example)
#define BCOPY2      LCTL(KC_INS)                // KC_CUT/COPY/PASTE
#define BPASTE2     LSFT(KC_INS)                // KC_CUT/COPY/PASTE
#define MOD_SHIFTS  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)) // Both shift keys (OR)

// Send unicode strings with your OS
#define LINUX_UNICODE(string)       SEND_STRING(SS_LCTL(SS_LSFT("u")) string "\n")
#define WINDOWS_CODE(string)        SEND_STRING(SS_LALT(string))
#define MACOS_CODE(string)          SEND_STRING(string)
#define MACOS_CODE1(string)         SEND_STRING(SS_LALT(string))
#define MACOS_CODE2(string)         SEND_STRING(SS_LALT(SS_LSFT(string)))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**   [Layer 0]         { Default: English [USA] }
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |   Browser   |   | Esc  |      |  F1  |  F2  |  F3  |  F4  |    |  F5  |  F6  |  F7  |  F8  |   |  F9  |  F10 |  F11 |  F12 |     | Print|Layout| Play |     |   1  |   2  |   3  |   4  |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    | Undo | Redo |   |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |   BackSpace   |     |Insert| Home | PgUp |     |BlkNum|   /  |   *  |   -  |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    | Term | Code |   |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |     \      |     |Delete|  End | PgDn |     |   7  |   8  |   9  |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|   +  |
     *    |  Cut | Open |   |  CapsLock  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |      Enter     |                                |   4  |   5  |   6  |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    | Copy | Close|   |  Shift        |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |          Shift     |            |   ^  |            |   1  |   2  |   3  |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|  Ent |
     *    | Paste| Save |   |  Ctrl  |  Alt   |  Cmd   |                S p a c e                  |   FN   |  AltG  |   Cmd  |  Ctrl  |     |   <  |   ¥  |   >  |     |   0         |   .  |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */  [_BASE_USA_] = LAYOUT(

            FKEY(F10),       KC_ESC,       KC_F1, KC_F2, KC_F3, KC_F4,      KC_F5, KC_F6, KC_F7, KC_F8,     KC_F9, KC_F10,KC_F11,KC_F12,      KC_PSCR,TO(1),  MO(4),  FKEY(F1),FKEY(F2),FKEY(F3),FKEY(F4),

           UNDO,REDO1,       KC_GRV,KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS, KC_EQL,      KC_BSPC,      KC_INS, KC_HOME,KC_PGUP,   KC_NLCK,KC_PSLS, KC_PAST,KC_PMNS,
       FKEY(F5),FKEY(F6),    KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_LBRC,KC_RBRC,   KC_BSLS,      KC_DEL, KC_END, KC_PGDN,   KC_P7,  KC_P8,   KC_P9,
          BCUT1,FKEY(F7),    KC_CAPS,     KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT,       KC_ENT,                                 KC_P4,  KC_P5,   KC_P6,  KC_PPLS,
         BCOPY1,FKEY(F8),    KC_LSFT,        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,              KC_UP,             KC_P1,  KC_P2,   KC_P3,
        BPASTE1,FKEY(F9),    KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                    MO(3),   KC_RALT, KC_RGUI, KC_RCTL,      KC_LEFT,KC_DOWN,KC_RGHT,   KC_P0,           KC_PDOT,KC_PENT
    ),

    // TODO: italian keyboard layout, work in progress
    /**   [Layer 1]         { Default: Italian layout }
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |Layout|      |     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |   \  |      |      |      |      |      |      |      |      |      |      |   '  |   ì  |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |      |      |      |      |      |      |      |      |   è  |   +  |      ù     |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |      |      |      |      |      |      |      |      |      |   ò  |   à  |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |      |      |   -  |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           |        |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */  [_BASE_ITA_] = LAYOUT(

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,TO(2),  KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

          KC_TRNS,KC_TRNS,   KC_BSLS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_QUOT,IGRAVE,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,EGRAVE,KC_PPLS,UGRAVE,   KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, OGRAVE,  AGRAVE,  KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_MINS,          KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),

    // TODO: USA International keyboard layout, work in progress
    /**   [Layer 2]         { Default: USA International Layout }
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |Layout|      |     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |   `  |      |      |      |      |      |      |      |      |      |      |   -  |   =  |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |      |      |      |      |      |      |      |      |   [  |   ]  |       \    |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |      |      |      |      |      |      |      |      |      |   ;  |   '  |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |   ,  |   .  |   /  |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           |        |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */  [_BASE_USA_INTL_] = LAYOUT(

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,TO(0),  KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

          KC_TRNS,KC_TRNS,   KC_GRV,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MINS,KC_EQL,KC_BSLS,   KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_LBRC,KC_RBRC,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_SCLN,KC_QUOT,   KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_COMM, KC_DOT, KC_SLSH,         KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),


    /**   [Layer 3]         { [LAYER EXT_FN]  Additional keys for all layouts }  FN = MO(3)
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |  Home Page  |   |StopM.|      |RecM.1|RecM.2|      |      |    |      |      |      |      |   |      |      |      |      |     |      |Chg-OS|      |     |      |      |      | Reset|
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      | Redo |   |      |      |      |      |   £  |      |      |      |      |      |      |      |      |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |   è  |      |      |      |   ù  |   ì  |   ò  |      |      |      |        §   |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |  Cut |      |   |            |   à  |      |      |      |      |      |      |      |      |      |      |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    | Copy |      |   |               |      |      |      |      |      |      | Mute |      |      |      |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    | Paste|      |   |        |        |        |                                           | ==FN== |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */
    [_EXT_FN_] = LAYOUT(

           KC_WWW_HOME,     DM_RSTP,  DM_REC1,DM_REC2,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,CHG_OS, KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,RESET,

          KC_TRNS,REDO2,    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,POUND,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,EGRAVE, KC_TRNS,KC_TRNS,KC_TRNS,UGRAVE,IGRAVE,OGRAVE, KC_TRNS,KC_TRNS,KC_TRNS,SECT1,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,
            BCUT2,KC_TRNS,  KC_TRNS, AGRAVE, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
           BCOPY2,KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS,
          BPASTE2,KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),


    /**   [Layer 4]         { [LAYER EXT_PLAY]  Additional keys for all layouts }  PLAY = MO(4)
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |Macro1|Macro2|      |      |    |      |      |      |      |   |      |      |      |      |     |      |      |=PLAY=|     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |      |      |      |      |      |      |      |      |      |      |      |      |      |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |      |      |      |      |      |      |      |      |      |      |            |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |      |      |      |      |      |      |      |      |      |      |      |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |      |      |      |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           |        |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */
    [_EXT_PLAY_] = LAYOUT(

          KC_TRNS,          KC_TRNS, DM_PLY1, DM_PLY2, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

     KC_TRNS,KC_TRNS,       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
     KC_TRNS,KC_TRNS,       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,
     KC_TRNS,KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
     KC_TRNS,KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS,
     KC_TRNS,KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    )

};




    /**   [Layer n]         { Layer description }       // Free keyboard comment, Copy'n'Paste to your new layer
     *
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |      |      |     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |      |      |      |      |      |      |      |      |      |      |      |      |      |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |      |      |      |      |      |      |      |      |      |      |            |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |      |      |      |      |      |      |      |      |      |      |      |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |      |      |      |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           |        |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */


void matrix_init_user(void) {
    osChange(LINUX);            // Default OS at startup
}

void matrix_scan_user(void) {
}

/**
 * Detect and process custom keycodes
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t modifiers;              // Key modifiers (ALT,SHIFT,CTRL,...), used in process_record_user()
    if (record->event.pressed) {
        switch (keycode) {
        
        /**
         * One shot keys. Not using ALTgr or other keys to compose
         * @see one liner case looks ugly but it's more compact in a quite crowded switch()
         */
        case CHG_OS:
            osToggle();
            return false;

        case POUND:     // £
            switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_6)); return false;
            case MACOS: MACOS_CODE1("3"); return false;
            case LINUX:
            default:    LINUX_UNICODE("a3"); return false;
            }
        case SECT1:     // §
            switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_7)); return false;
            case MACOS: MACOS_CODE("6"); return false;
            case LINUX:
            default:    LINUX_UNICODE("a7"); return false;
            }
        case AGRAVE:    // àÀ
            modifiers = get_mods();
            clear_mods();
            if (modifiers & MOD_SHIFTS) {   // À
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_2)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "A"); return false;
                case LINUX:
                default:    LINUX_UNICODE("c0"); return false;
                }
            } else {                        // à
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_4)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "a"); return false;
                case LINUX:
                default:    LINUX_UNICODE("e0"); return false;
                }
            }
        case EGRAVE:    // èÈ
            modifiers = get_mods();
            clear_mods();
            if (modifiers & MOD_SHIFTS) {   // È
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_0)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "E"); return false;
                case LINUX:
                default:    LINUX_UNICODE("c8"); return false;
                }
            } else {                        // è
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_2)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "e"); return false;
                case LINUX:
                default:    LINUX_UNICODE("e8"); return false;
                }
            }
        case IGRAVE:    // ìÌ
            modifiers = get_mods();
            clear_mods();
            if (modifiers & MOD_SHIFTS) {   // Ì
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_4)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "I"); return false;
                case LINUX:
                default:    LINUX_UNICODE("cc"); return false;
                }
            } else {                        // ì
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_6)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "i"); return false;
                case LINUX:
                default:    LINUX_UNICODE("ec"); return false;
                }
            }
        case OGRAVE:    // òÒ
            modifiers = get_mods();
            clear_mods();
            if (modifiers & MOD_SHIFTS) {   // Ò
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_0)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "O"); return false;
                case LINUX:
                default:    LINUX_UNICODE("d2"); return false;
                }
            } else {                        // ò
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_2)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "o"); return false;
                case LINUX:
                default:    LINUX_UNICODE("f2"); return false;
                }
            }
        case UGRAVE:    // ùÙ
            modifiers = get_mods();
            clear_mods();
            if (modifiers & MOD_SHIFTS) {   // Ù
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_7)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "U"); return false;
                case LINUX:
                default:    LINUX_UNICODE("d9"); return false;
                }
            } else {                        // ù
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_9)); return false;
                case MACOS: MACOS_CODE(SS_LALT("`") "u"); return false;
                case LINUX:
                default:    LINUX_UNICODE("f9"); return false;
                }
            }

        case KC_A:
            modifiers = get_mods();
            if (modifiers & MOD_BIT(KC_RALT)) { // áÁ
                clear_mods();
                if (modifiers & MOD_SHIFTS) {   // Á
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_3)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "A"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("c1"); return false;
                    }
                } else {                        // á
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_5)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "a"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("e1"); return false;
                    }
                }
            }
            break;

        case KC_E:
            modifiers = get_mods();
            if (modifiers & MOD_BIT(KC_RALT)) { // éÉ
                clear_mods();
                if (modifiers & MOD_SHIFTS) {   // É
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_1)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "E"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("c9"); return false;
                    }
                } else {                        // é
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_3)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "e"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("e9"); return false;
                    }
                }
            }
            break;

        case KC_I:
            modifiers = get_mods();
            if (modifiers & MOD_BIT(KC_RALT)) { // íÍ
                clear_mods();
                if (modifiers & MOD_SHIFTS) {   // Í
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_5)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "I"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("cd"); return false;
                    }
                } else {                        // í
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_7)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "i"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("ed"); return false;
                    }
                }
            }
            break;

        case KC_O:
            modifiers = get_mods();
            if (modifiers & MOD_BIT(KC_RALT)) { // óÓ
                clear_mods();
                if (modifiers & MOD_SHIFTS) {   // Ó
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_1)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "O"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("d3"); return false;
                    }
                } else {                        // ó
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_3)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "o"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("f3"); return false;
                    }
                }
            }
            break;

        case KC_U:
            modifiers = get_mods();
            if (modifiers & MOD_BIT(KC_RALT)) { // úÚ
                clear_mods();
                if (modifiers & MOD_SHIFTS) {   // Ú
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_8)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "U"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("da"); return false;
                    }
                } else {                        // ú
                    switch (osCurrent()) {
                    case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_0)); return false;
                    case MACOS: MACOS_CODE(SS_LALT("e") "u"); return false;
                    case LINUX:
                    default:    LINUX_UNICODE("fa"); return false;
                    }
                }
            }
            break;

        case KC_4:
            modifiers = get_mods();
            if (modifiers & MOD_BIT(KC_RALT)) { // Euro Sign [€]
                clear_mods();
                switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_2) SS_TAP(X_KP_8)); return false;
                case MACOS: MACOS_CODE2("2"); return false;
                case LINUX:
                default:    LINUX_UNICODE("20ac"); return false;
                }
            }
            break;

        }   // Switch end
    }       // if keyPressed end
    return true;
} /**/


/**
 * User function, activated when layer changes
 * When layer changes inform the other Teensy about that through serial
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _BASE_USA_:
            layout(PSTR("EN"));
            break;
        case _BASE_ITA_:
            layout(PSTR("IT"));
            break;
        case _BASE_USA_INTL_:
            layout(PSTR("UI"));
            break;
    }
    return state;
} /**/


// No leds to handle here (just a stub)
void led_set_user(uint8_t usb_led) {
} /**/
