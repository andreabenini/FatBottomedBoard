/* Copyright 2020 Ben
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
 */
#include QMK_KEYBOARD_H


    /**
     * [FatBottomedBoard Layout Template]      { 119 keymap, 20x6 }
     *
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |   Browser   |   | Esc  |      |  F1  |  F2  |  F3  |  F4  |    |  F5  |  F6  |  F7  |  F8  |   |  F9  |  F10 |  F11 |  F12 |     | Print|Switch| Macro|     |   1  |   2  |   3  |   4  | 21
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
    _BASE_USA_INTL_,
    _BASE_ITA_,
    _BASE_USA_,
    _EXT_FN_
};


// Defines custom key codes
enum custom_keycodes {
    CHG_OS = SAFE_RANGE,
    AGRAVE,
    EGRAVE,
    IGRAVE,
    OGRAVE,
    UGRAVE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**   [Layer 0]         { Default: USA International }
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |   Browser   |   | Esc  |      |  F1  |  F2  |  F3  |  F4  |    |  F5  |  F6  |  F7  |  F8  |   |  F9  |  F10 |  F11 |  F12 |     | Print|Layout| Macro|     |   1  |   2  |   3  |   4  |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    | Undo | Redo |   |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |   BackSpace   |     |Insert| Home | PgUp |     |BlkNum|   /  |   *  |   -  |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    | Term | Code |   |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |     \      |     |Delete|  End | PgDn |     |   7  |   8  |   9  |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|   +  |
     *    |  Cut | Open |   |  CapsLock  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |      Enter     |                                |   4  |   5  |   6  |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    | Copy | Close|   |  Shift        |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |          Shift     |            |   ^  |            |   1  |   2  |   3  |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|  Ent |
     *    | Paste| Save |   |  Ctrl  |  Alt   |  Cmd   |                S p a c e                  |   FN   |  AltG  |   Cmd  |  Ctrl  |     |   <  |   ¥  |   >  |     |   0         |   .  |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */  [_BASE_USA_INTL_] = LAYOUT(

               KC_F20,       KC_ESC,       KC_F1, KC_F2, KC_F3, KC_F4,      KC_F5, KC_F6, KC_F7, KC_F8,     KC_F9, KC_F10,KC_F11,KC_F12,      KC_PSCR,TO(1),  KC_TRNS,   KC_F21, KC_F22,  KC_F23, KC_F24, 

          KC_UNDO,KC_AGAIN,  KC_GRV,KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS, KC_EQL,      KC_BSPC,      KC_INS, KC_HOME,KC_PGUP,   KC_NLCK,KC_PSLS, KC_PAST,KC_PMNS, 
           KC_F15,KC_F16,    KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_LBRC,KC_RBRC,   KC_BSLS,      KC_DEL, KC_END, KC_PGDN,   KC_P7,  KC_P8,   KC_P9, 
           KC_CUT,KC_F17,    KC_CAPS,     KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT,       KC_ENT,                                 KC_P4,  KC_P5,   KC_P6,  KC_PPLS,
          KC_COPY,KC_F18,    KC_LSFT,        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,              KC_UP,             KC_P1,  KC_P2,   KC_P3,
         KC_PASTE,KC_F19,    KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                    MO(3),   KC_RALT, KC_RGUI, KC_RCTL,      KC_LEFT,KC_DOWN,KC_RGHT,   KC_P0,           KC_PDOT,KC_PENT
    ),

    /**   [Layer 1]         { Default: Italian layout }
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |Layout|      |     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |      |      |      |      |      |      |      |      |      |      |      |   '  |      |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |      |      |      |      |      |      |      |      |      |      |            |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |      |      |      |      |      |      |      |      |      |      |      |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |      |      |   -  |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           |        |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */  [_BASE_ITA_] = LAYOUT(

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,TO(2),KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 

          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_QUOT,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_MINS,          KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),

    /**   [Layer 1]         { Default: USA layout }
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |Layout|      |     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |      |      |      |      |      |      |      |      |      |      |      |      |      |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |      |      |      |      |      |      |      |      |      |      |            |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |      |      |      |      |      |      |      |      |      |      |      |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |      |      |   [  |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           |        |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */  [_BASE_USA_] = LAYOUT(

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,TO(0),  KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 

          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_LBRC,          KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),



    /**   [Layer FN]        { Additional keys for [USA International] }  FN = MO(3)
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |Chg-OS| Reset|     |      |      |      |      |
     *    `-------------'   `------'      `------'------'------'------'    `------'------'------'------'   `------'------'------'------'     `------'------'------'     `------'------'------'------'
     *    ,-------------.   ,------.------.------.------.------.------.------.------.------.------.------.------.------.---------------.     ,------,------,------.     ,------,------,------,------.
     *    |      |      |   |      |      |      |      |      |      |      |      |      |      |      |      |      |               |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     .------+------+------'     '------+------+------+------'
     *    |      |      |   |         |      |      |   é  |      |      |      |   ú  |   í  |   ó  |      |      |      |            |     |      |      |      |     |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'     `------'------'------'     '------+------+------|      |
     *    |      |      |   |            |   á  |      |      |      |      |      |      |      |      |      |      |                |                                |      |      |      |      |
     *    |------+------'   .----------------------------------------------------------------------------------------------------------'            ,------.            '------+------+------+------'
     *    |      |      |   |               |      |      |      |      |      |      |      |      |      |      |                    |            |      |            |      |      |      |      |
     *    |------+------'   .--------,--------,--------,-------------------------------------------.--------.--------.--------.--------.     ,------+------+------.     '------'------+------|      |
     *    |      |      |   |        |        |        |                                           | ==FN== |        |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */
    [_EXT_FN_] = LAYOUT(

          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,CHG_OS, RESET,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 

     KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
     KC_TRNS,KC_TRNS,       KC_TRNS,KC_TRNS,KC_TRNS,EGRAVE,KC_TRNS,KC_TRNS,KC_TRNS,UGRAVE,IGRAVE,OGRAVE,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, 
     KC_TRNS,KC_TRNS,       KC_TRNS, AGRAVE, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
     KC_TRNS,KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS, 
     KC_TRNS,KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    )
};


// Free keyboard comment, copy 'n' paste to your new layer

    /**   [Layer n]         { Layer description }
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
    osChange(LINUX);            // Default OS
}

void matrix_scan_user(void) {

    // uint8_t layer = biton32(layer_state);
    // switch (layer) {
    //     case _BASE_ITA_:
    //         // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_1
    //         break;
    //     // add case for each layer
    // }

}


/**
 * Detect and process custom keycodes
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case CHG_OS:
            osToggle();
        case AGRAVE:
            // TODO: Rewrite without keyboards shortcuts (not cross portable across OSes)
            SEND_STRING(SS_LALT("D83D+DC4D"));
            // SEND_STRING(SS_DOWN(X_RALT));
            // SEND_STRING(SS_TAP(X_GRV));
            // SEND_STRING(SS_UP(X_RALT));
            // SEND_STRING(SS_TAP(X_A));
            return false;
        case EGRAVE:
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_TAP(X_GRV));
            SEND_STRING(SS_UP(X_RALT));
            SEND_STRING(SS_TAP(X_E));
            return false;
        case IGRAVE:
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_TAP(X_GRV));
            SEND_STRING(SS_UP(X_RALT));
            SEND_STRING(SS_TAP(X_I));
            return false;
        case OGRAVE:
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_TAP(X_GRV));
            SEND_STRING(SS_UP(X_RALT));
            SEND_STRING(SS_TAP(X_O));
            return false;
        case UGRAVE:
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_TAP(X_GRV));
            SEND_STRING(SS_UP(X_RALT));
            SEND_STRING(SS_TAP(X_U));
            return false;
        }
    }
    return true;
} /**/


/**
 * User function, activated when layer changes
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _BASE_USA_INTL_:
            layout(PSTR("UI"));
            break;
        case _BASE_ITA_:
            layout(PSTR("IT"));
            break;
        case _BASE_USA_:
            layout(PSTR("US"));
            break;
    }
    return state;
} /**/


void led_set_user(uint8_t usb_led) {
}
