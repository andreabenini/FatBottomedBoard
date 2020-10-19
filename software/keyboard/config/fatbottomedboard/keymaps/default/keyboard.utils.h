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
#define LINUX_UNICODE(string)       SEND_STRING(SS_LCTL(SS_LSFT("u")) string "\n")
#define WINDOWS_CODE(string)        SEND_STRING(SS_LALT(string))
#define MACOS_CODE(string)          SEND_STRING(string)
#define MACOS_CODE1(string)         SEND_STRING(SS_LALT(string))
#define MACOS_CODE2(string)         SEND_STRING(SS_LALT(SS_LSFT(string)))

// required functions
bool keyboardPrintPound(void);      // £
bool keyboardPrintSection1(void);   // §
bool keyboardPrintCedilla(void);    // ç
bool keyboardPrintDegree(void);     // °

// ITA Keyboard
bool keyboardPrintTwoIT(void);
bool keyboardPrintThreeIT(void);
bool keyboardPrintSixIT(void);
bool keyboardPrintSevenIT(void);
bool keyboardPrintEightIT(void);
bool keyboardPrintNineIT(void);
bool keyboardPrintZeroIT(void);
bool keyboardPrintQuotIT(void);
bool keyboardPrintIGraveIT(void);
bool keyboardPrintEGraveIT(void);
bool keyboardPrintPlusIT(void);
bool keyboardPrintUGraveIT(void);
bool keyboardPrintOGraveIT(void);
bool keyboardPrintAGraveIT(void);
bool keyboardPrintCommaIT(void);
bool keyboardPrintDotIT(void);
bool keyboardPrintMinusIT(void);

// Generic keys (EN-USA)
bool keyboardPrintAGrave(void);
bool keyboardPrintEGrave(void);
bool keyboardPrintIGrave(void);
bool keyboardPrintOGrave(void);
bool keyboardPrintUGrave(void);
bool keyboardPrintAAcute(void);
bool keyboardPrintEAcute(void);
bool keyboardPrintEuroIfNeeded(void);
bool keyboardPrintAAcuteIfNeeded(void);
bool keyboardPrintEAcuteIfNeeded(void);
bool keyboardPrintIAcuteIfNeeded(void);
bool keyboardPrintOAcuteIfNeeded(void);
bool keyboardPrintUAcuteIfNeeded(void);

#endif
