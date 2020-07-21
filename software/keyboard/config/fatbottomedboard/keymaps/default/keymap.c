#include QMK_KEYBOARD_H
#include "benmaps.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE_US_INTL_,
    _BASE_ITA_,
    _BASE_US_,
    _FN3
};

/**
 *    [FatBottomedBoard Layout Template]      { 119 keymap, 20x6 }
 * 
 *    ,---------.   ,---.   ,---,---,---,---.  ,---,---,---,---.  ,---,---,---,---.  ,---,---,---.  ,---,---,---,---.
 *    |   WWW   |   |Esc|   | F1| F2| F3| F4|  | F5| F6| F7| F8|  | F9|F10|F11|F12|  |Prt|SwL|Mac|  |  1|  2|  3|  4|
 *    `---------'   `---'   `---'---'---'---'  `---'---'---'---'  `---'---'---'---'  `---'---'---'  `---'---'---'---'
 *    ,---------.   ,---.---.---.---.---.---.---.---.---.---.---.---.---.---------.  ,---,---,---.  ,---,---,---,---.
 *    |Undo|Redo|   | ~ |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  BackSp |  |Ins|Hom|PgU|  |Num| / | * | - |
 *    |----+----'   .-------------------------------------------------------------'  .---+---+---'  '---+---+---+---'
 *    |Term|Code|   | Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \   |  |Del|End|PgD|  |  7|  8|  9|   |
 *    |----+----'   .-------------------------------------------------------------'  `---'---'---'  '---+---+---| + |
 *    |Cut |Open|   | Caps |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|   Enter  |                 |  4|  5|  6|   |
 *    |----+----'   .-------------------------------------------------------------'      ,---.      '---+---+---+---'
 *    |Copy|Clos|   | Shift |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|    Shift    |      | ^ |      |  1|  2|  3|   |
 *    |----+----'   .----,----,----,--------------------------.----.----.----.----.  ,---+---+---.  '---'---+---|Ent|
 *    |Past|Save|   |Ctrl|Alt |Cmd |         S p a c e        |AltG| FN |Cmd |Ctrl|  | < | ¥ | > |  |     0 | . |   |
 *    `----'----'   `----'----'----`--------------------------'----'----'----'----'  `---'---'---'  `-------'---'---'
 * 
 * 
 *    - ROW -  1   2   3   4   5   6
 *      pin   C2  C3  C4  C5  C6  C7
 * 
 *    - COL -  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
 *      pin   F2  F1  F0  E6  E7  B0  B1  B2  B3  B4  B5  B6  B7  D4  D5  D7  E0  E1  C0  C1
 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**   [Layer 0]         { Default: US International }
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
     *    | Paste| Save |   |  Ctrl  |  Alt   |  Cmd   |                S p a c e                  |  AltG  |   FN   |   Cmd  |  Ctrl  |     |   <  |   ¥  |   >  |     |   0         |   .  |      | 16
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */
	[_BASE_US_INTL_] = LAYOUT(

               KC_F20,       KC_ESC,       KC_F1, KC_F2, KC_F3, KC_F4,      KC_F5, KC_F6, KC_F7, KC_F8,     KC_F9, KC_F10,KC_F11,KC_F12,      KC_PSCR,DF(1),RESET,       KC_F21, KC_F22,  KC_F23, KC_F24, 

          KC_UNDO,KC_AGAIN,  KC_GRV,KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS, KC_EQL,      KC_BSPC,      KC_INS,KC_HOME,KC_PGUP,    KC_NLCK,KC_PSLS, KC_PAST,KC_PMNS, 
           KC_F15,KC_F16,    KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_LBRC,KC_RBRC,   KC_BSLS,      KC_DEL,KC_END,KC_PGDN,     KC_P7,  KC_P8,   KC_P9, 
           KC_CUT,KC_F17,    KC_CAPS,     KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT,       KC_ENT,                                 KC_P4,  KC_P5,   KC_P6,  KC_PPLS,
          KC_COPY,KC_F18,    KC_LSFT,        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,              KC_UP,             KC_P1,  KC_P2,   KC_P3,
         KC_PASTE,KC_F19,    KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                    KC_RALT, MO(3),  KC_RGUI,  KC_RCTL,      KC_LEFT,KC_DOWN,KC_RGHT,   KC_P0,  KC_PDOT,         KC_PENT
    ),

    [_BASE_ITA_] = LAYOUT(          // Italian base keyboard

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,DF(2),KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 

          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_QUOT,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_MINS,          KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,                     KC_TRNS,                      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),

    [_BASE_US_] = LAYOUT(           // US keyboard

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,DF(0),KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 

          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MINS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_SLSH,          KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,                   KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
    ),


    /**   [Layer 3]         { Additional keys for [US International] }  FN = MO(3)
     * 
     *    ,-------------.   ,------.      ,------,------,------,------.    ,------,------,------,------.   ,------,------,------,------.     ,------,------,------.     ,------,------,------,------.
     *    |             |   |      |      |      |      |      |      |    |      |      |      |      |   |      |      |      |      |     |      |      |      |     |      |      |      |      |
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
     *    |      |      |   |        |        |        |                                           |        | --==-- |        |        |     |      |      |      |     |             |      |      |
     *    `------'------'   `--------'--------'--------`-------------------------------------------'--------'--------'--------'--------'     `------'------'------'     `-------------'------'------'
     */
    [_FN3] = LAYOUT(

              KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 

          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,_EACUTE,KC_TRNS,KC_TRNS,KC_TRNS,_UACUTE,_IACUTE,_OACUTE,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,_AACUTE,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,          KC_TRNS,              KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS, 
          KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,                   KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,        KC_TRNS,KC_TRNS
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




/*
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool led_update_user(led_t led_state) {
    return true;
}
*/
