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
#include "keyboard.utils.h"

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
    SECT1,      // §
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

          KC_TRNS,KC_TRNS,   KC_GRV,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MINS,KC_EQL,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
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
    if (record->event.pressed) {
        switch (keycode) {
        
        // One shot keys. Not using ALTgr or other keys to compose
        case CHG_OS:
            osToggle();
            return false;
        case POUND:     // £
            return keyboardPrintPound();
        case SECT1:     // §
            return keyboardPrintSection1();
        case AGRAVE:    // àÀ
            return keyboardPrintAGrave();
        case EGRAVE:    // èÈ
            return keyboardPrintEGrave();
        case IGRAVE:    // ìÌ
            return keyboardPrintIGrave();
        case OGRAVE:    // òÒ
            return keyboardPrintOGrave();
        case UGRAVE:    // ùÙ
            return keyboardPrintUGrave();

        // AltGr dependent keys. Convert to symbol only if needed
        case KC_A:      // áÁ
            return keyboardPrintAAcuteIfNeeded();
        case KC_E:      // éÉ
            return keyboardPrintEAcuteIfNeeded();
        case KC_I:      // íÍ
            return keyboardPrintIAcuteIfNeeded();
        case KC_O:      // íÍ
            return keyboardPrintOAcuteIfNeeded();
        case KC_U:      // úÚ
            return keyboardPrintUAcuteIfNeeded();
        case KC_4:      // €
            return keyboardPrintEuroIfNeeded();
        }
    }   // if keyPressed end
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
