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
#ifndef __KEYBOARD_UTILS__
#define __KEYBOARD_UTILS__

#pragma once
#include QMK_KEYBOARD_H


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
#define LINUX_UNICODE(string)                   SEND_STRING(SS_LCTL(SS_LSFT("u")) string SS_TAP(X_ENT))
#define MACOS_CODE(string)                      SEND_STRING(string)
#define MACOS_CODE1(string)                     SEND_STRING(SS_LALT(string))
#define MACOS_CODE2(string)                     SEND_STRING(SS_LALT(SS_LSFT(string)))
#define WINDOWS_CODE(string)                    SEND_STRING(SS_LALT(string))

// required functions

// Special characters
bool keyboardPrintPound(void);                  // £
bool keyboardPrintSection1(void);               // §
bool keyboardPrintCedilla(void);                // ç
bool keyboardPrintDegree(void);                 // °
bool keyboardPrintEuro(void);                   // €


// ITA Keyboard
bool keyboardPrintTwoIT_ON(void);               bool keyboardPrintTwoIT_OFF(void);
bool keyboardPrintThreeIT_ON(void);             bool keyboardPrintThreeIT_OFF(void);
bool keyboardPrintSixIT_ON(void);               bool keyboardPrintSixIT_OFF(void);
bool keyboardPrintSevenIT_ON(void);             bool keyboardPrintSevenIT_OFF(void);
bool keyboardPrintEightIT_ON(void);             bool keyboardPrintEightIT_OFF(void);
bool keyboardPrintNineIT_ON(void);              bool keyboardPrintNineIT_OFF(void);
bool keyboardPrintZeroIT_ON(void);              bool keyboardPrintZeroIT_OFF(void);
bool keyboardPrintQuotIT_ON(void);              bool keyboardPrintQuotIT_OFF(void);
bool keyboardPrintIGraveIT_ON(void);            bool keyboardPrintIGraveIT_OFF(void);
bool keyboardPrintEGraveIT_ON(void);            bool keyboardPrintEGraveIT_OFF(void);
bool keyboardPrintPlusIT_ON(void);              bool keyboardPrintPlusIT_OFF(void);
bool keyboardPrintUGraveIT_ON(void);
bool keyboardPrintOGraveIT_ON(void);            bool keyboardPrintOGraveIT_OFF(void);
bool keyboardPrintAGraveIT_ON(void);            bool keyboardPrintAGraveIT_OFF(void);
bool keyboardPrintCommaIT_ON(void);             bool keyboardPrintCommaIT_OFF(void);
bool keyboardPrintDotIT_ON(void);               bool keyboardPrintDotIT_OFF(void);
bool keyboardPrintMinusIT_ON(void);             bool keyboardPrintMinusIT_OFF(void);

// Generic keys (EN-USA)
bool keyboardPrintFour_ON(void);

bool keyboardPrintAGrave(void);
bool keyboardPrintEGrave(void);
bool keyboardPrintIGrave(void);
bool keyboardPrintOGrave(void);
bool keyboardPrintUGrave(void);
bool keyboardPrintAAcute(void);
bool keyboardPrintEAcute(void);
bool keyboardPrintIAcute(void);
bool keyboardPrintOAcute(void);
bool keyboardPrintUAcute(void);

#endif
