#include "keyboard.utils.h"
#include "fatbottomedboard.h"

bool keyboardPrintPound(void) {
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_6)); return false;
        case MACOS: MACOS_CODE1("3"); return false;
        case LINUX:
        default:    LINUX_UNICODE("a3"); return false;
    }
} /**/

bool keyboardPrintSection1(void) {
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_7)); return false;
        case MACOS: MACOS_CODE("6"); return false;
        case LINUX:
        default:    LINUX_UNICODE("a7"); return false;
    }
} /**/


bool keyboardPrintAGrave(void) {
    // TODO: work in progress on keyboard detection
    // char sss[10];       
    // sprintf(sss, "%lu", layer_state);
    // send_string(sss);
    // TODO: END
    // À
    if (get_mods() & MOD_SHIFTS) {       
        clear_mods();
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_2)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "A"); return false;
            case LINUX:
            default:    LINUX_UNICODE("c0"); return false;
        }
    }
    // à
    clear_mods();
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_4)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "a"); return false;
        case LINUX:
        default:    LINUX_UNICODE("e0"); return false;
    }
} /**/

bool keyboardPrintEGrave(void) {
    // È
    if (get_mods() & MOD_SHIFTS) {       
        clear_mods();
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_0)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "E"); return false;
            case LINUX:
            default:    LINUX_UNICODE("c8"); return false;
        }
    }
    // è
    clear_mods();
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_2)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "e"); return false;
        case LINUX:
        default:    LINUX_UNICODE("e8"); return false;
    }
} /**/

bool keyboardPrintIGrave(void) {
    // Ì
    if (get_mods() & MOD_SHIFTS) {
        clear_mods();
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_4)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "I"); return false;
            case LINUX:
            default:    LINUX_UNICODE("cc"); return false;
        }
    }
    // ì
    clear_mods();
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_6)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "i"); return false;
        case LINUX:
        default:    LINUX_UNICODE("ec"); return false;
    }
} /**/

bool keyboardPrintOGrave(void) {
    // Ò
    if (get_mods() & MOD_SHIFTS) {       
        clear_mods();
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_0)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "O"); return false;
            case LINUX:
            default:    LINUX_UNICODE("d2"); return false;
        }
    }
    // ò
    clear_mods();
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_2)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "o"); return false;
        case LINUX:
        default:    LINUX_UNICODE("f2"); return false;
    }
} /**/

bool keyboardPrintUGrave(void) {
    // Ù
    if (get_mods() & MOD_SHIFTS) {   
        clear_mods();
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_7)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "U"); return false;
            case LINUX:
            default:    LINUX_UNICODE("d9"); return false;
        }
    }
    // ù
    clear_mods();
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_9)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "u"); return false;
        case LINUX:
        default:    LINUX_UNICODE("f9"); return false;
    }
} /**/


bool keyboardPrintAAcuteIfNeeded() {
    uint8_t modifiers = get_mods();         // Key modifiers (ALT,SHIFT,CTRL,...), used in process_record_user()
    if (modifiers & MOD_BIT(KC_RALT)) {     // áÁ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {       // Á
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_3)); return false;
                case MACOS: MACOS_CODE(SS_LALT("e") "A"); return false;
                case LINUX:
                default:    LINUX_UNICODE("c1"); return false;
            }
        }
        // á
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_5)); return false;
            case MACOS: MACOS_CODE(SS_LALT("e") "a"); return false;
            case LINUX:
            default:    LINUX_UNICODE("e1"); return false;
        }
    }
    return true;
} /**/

bool keyboardPrintEAcuteIfNeeded() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) {     // éÉ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {       // É
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_1)); return false;
                case MACOS: MACOS_CODE(SS_LALT("e") "E"); return false;
                case LINUX:
                default:    LINUX_UNICODE("c9"); return false;
            }
        }
        // é
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_3)); return false;
            case MACOS: MACOS_CODE(SS_LALT("e") "e"); return false;
            case LINUX:
            default:    LINUX_UNICODE("e9"); return false;
        }
    }
    return true;
} /**/

bool keyboardPrintIAcuteIfNeeded() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) { // íÍ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {   // Í
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_5)); return false;
                case MACOS: MACOS_CODE(SS_LALT("e") "I"); return false;
                case LINUX:
                default:    LINUX_UNICODE("cd"); return false;
            }
        }
        // í
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_7)); return false;
            case MACOS: MACOS_CODE(SS_LALT("e") "i"); return false;
            case LINUX:
            default:    LINUX_UNICODE("ed"); return false;
        }
    }
    return true;
} /**/

bool keyboardPrintOAcuteIfNeeded() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) { // óÓ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {   // Ó
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_1)); return false;
                case MACOS: MACOS_CODE(SS_LALT("e") "O"); return false;
                case LINUX:
                default:    LINUX_UNICODE("d3"); return false;
            }
        }
        // ó
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_3)); return false;
            case MACOS: MACOS_CODE(SS_LALT("e") "o"); return false;
            case LINUX:
            default:    LINUX_UNICODE("f3"); return false;
        }
    }
    return true;
} /**/

bool keyboardPrintUAcuteIfNeeded() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) { // úÚ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {   // Ú
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_8)); return false;
                case MACOS: MACOS_CODE(SS_LALT("e") "U"); return false;
                case LINUX:
                default:    LINUX_UNICODE("da"); return false;
            }
        }
        // ú
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_0)); return false;
            case MACOS: MACOS_CODE(SS_LALT("e") "u"); return false;
            case LINUX:
            default:    LINUX_UNICODE("fa"); return false;
        }
    }
    return true;
} /**/

bool keyboardPrintEuroIfNeeded() {
    if (get_mods() & MOD_BIT(KC_RALT)) { // Euro Sign [€]
        clear_mods();
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_2) SS_TAP(X_KP_8)); return false;
            case MACOS: MACOS_CODE2("2"); return false;
            case LINUX:
            default:    LINUX_UNICODE("20ac"); return false;
        }
    }
    return true;
} /**/
