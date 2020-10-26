#include "keyboard.utils.h"
#include "fatbottomedboard.h"

/**
 * @see keyboard detection
 *      sprintf(sss, "%lu %d %d %d ..%d..", layer_state, 
 *                   _BASE_USA_,
 *                   _BASE_ITA_,
 *                   _BASE_USA_INTL_,
 *                   IS_LAYER_ON(_BASE_USA_) // Funziona !!!
 *      );
 *      send_string(sss);
 * #define IS_LAYER_ON(layer)  (layer_state & (1UL << (layer)))
 */


bool keyboardPrintPound() {                 // £
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_6)); return false;
        case MACOS: MACOS_CODE1("3");    return false;
        case LINUX:
        default:    LINUX_UNICODE("a3"); return false;
    }
} /**/

bool keyboardPrintEuro() {                  // Euro Sign [€]
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_2) SS_TAP(X_KP_8)); return false;
        case MACOS: MACOS_CODE2("2"); return false;
        case LINUX:
        default:    LINUX_UNICODE("20ac"); return false;
    }
} /**/

bool keyboardPrintSection1() {              // §
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_2) SS_TAP(X_KP_1)); return false;
        case MACOS: MACOS_CODE("6");     return false;
        case LINUX:
        default:    LINUX_UNICODE("a7"); return false;
    }
} /**/

bool keyboardPrintCedilla() {               // ç
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_1)); return false;
        case MACOS: MACOS_CODE1("c");    return false;
        case LINUX:
        default:    LINUX_UNICODE("e7"); return false;
    }
} /**/

bool keyboardPrintDegree() {                // °
    switch (osCurrent()) {
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_6)); return false;
        case MACOS: MACOS_CODE2("8");    return false;
        case LINUX:
        default:    LINUX_UNICODE("b0"); return false;
    }
} /**/

bool keyboardPrintAGrave() {                // Àà
    if (get_mods() & MOD_SHIFTS) {          // À
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_2)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "A"); return false;
            case LINUX:
            default:    LINUX_UNICODE("c0"); return false;
        }
    }
    switch (osCurrent()) {                  // à
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_4)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "a"); return false;
        case LINUX:
        default:    LINUX_UNICODE("e0"); return false;
    }
} /**/

bool keyboardPrintEGrave() {                // Èè
    if (get_mods() & MOD_SHIFTS) {          // È
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_0)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "E"); return false;
            case LINUX:
            default:    LINUX_UNICODE("c8"); return false;
        }
    }
    switch (osCurrent()) {                  // è
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_2)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "e"); return false;
        case LINUX:
        default:    LINUX_UNICODE("e8"); return false;
    }
} /**/

bool keyboardPrintIGrave() {                // Ìì
    if (get_mods() & MOD_SHIFTS) {          // Ì
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_4)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "I"); return false;
            case LINUX:
            default:    LINUX_UNICODE("cc"); return false;
        }
    }
    switch (osCurrent()) {                  // ì
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_6)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "i"); return false;
        case LINUX:
        default:    LINUX_UNICODE("ec"); return false;
    }
} /**/

bool keyboardPrintOGrave() {                // Òò
    if (get_mods() & MOD_SHIFTS) {          // Ò
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_0)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "O"); return false;
            case LINUX:
            default:    LINUX_UNICODE("d2"); return false;
        }
    }
    switch (osCurrent()) {                  // ò
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_2)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "o"); return false;
        case LINUX:
        default:    LINUX_UNICODE("f2"); return false;
    }
} /**/

bool keyboardPrintUGrave() {                // Ùù
    if (get_mods() & MOD_SHIFTS) {          // Ù
        switch (osCurrent()) {
            case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_7)); return false;
            case MACOS: MACOS_CODE(SS_LALT("`") "U"); return false;
            case LINUX:
            default:    LINUX_UNICODE("d9"); return false;
        }
    }
    switch (osCurrent()) {                  // ù
        case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_9)); return false;
        case MACOS: MACOS_CODE(SS_LALT("`") "u"); return false;
        case LINUX:
        default:    LINUX_UNICODE("f9"); return false;
    }
} /**/




/**
 * GENERIC KEYBOARD FUNCTIONS
 */

bool keyboardPrintFour_ON() {
    if (get_mods() & MOD_BIT(KC_RALT)) {    // Pound Sterlin [£]
        clear_mods();
        return keyboardPrintPound();
    }
    return true;
} /**/




/**
 * ITALIAN KEYBOARD FUNCTIONS
 */

bool keyboardPrintTwoIT_ON() {              // 2"
    if (get_mods() & MOD_SHIFTS) {          // "
        register_code(KC_LSHIFT);
        register_code(KC_QUOTE);
    } else {
        register_code(KC_2);                // 2
    }
    return false;
} /**/
bool keyboardPrintTwoIT_OFF() {             // 2"
    if (get_mods() & MOD_SHIFTS) {
        unregister_code(KC_QUOTE);
        unregister_code(KC_LSHIFT);
    } else {
        unregister_code(KC_2);
    }
    return false;
}

bool keyboardPrintThreeIT_ON() {            // 3£
    if (get_mods() & MOD_SHIFTS) {          // £
        return keyboardPrintPound();
    }
    register_code(KC_3);                    // 3
    return false;
} /**/
bool keyboardPrintThreeIT_OFF() {           // 3£
    if (get_mods() & MOD_SHIFTS) {          // £
        return false;   // do nothing
    }
    unregister_code(KC_3);                  // 3
    return false;
} /**/


bool keyboardPrintSixIT_ON() {              // 6&
    if (get_mods() & MOD_SHIFTS) {          // &
        register_code(KC_7);
    } else {                                // 6
        register_code(KC_6);
    }
    return false;
} /**/
bool keyboardPrintSixIT_OFF() {             // 6&
    if (get_mods() & MOD_SHIFTS) {          // &
        unregister_code(KC_7);
    } else {                                // 6
        unregister_code(KC_6);
    }
    return false;
} /**/

bool keyboardPrintSevenIT_ON() {            // 7/
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // /
        clear_mods();
        register_code(KC_SLASH);
        set_mods(modifier);
    } else {
        register_code(KC_7);                // 7
    }
    return false;
} /**/
bool keyboardPrintSevenIT_OFF() {
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // /
        clear_mods();
        unregister_code(KC_SLASH);
        set_mods(modifier);
    } else {
        unregister_code(KC_7);              // 7
    }
    return false;
} /**/

bool keyboardPrintEightIT_ON() {            // 8(
    if (get_mods() & MOD_SHIFTS) {          // (
        register_code(KC_9);
    } else {                                // 8
        register_code(KC_8);
    }
    return false;
} /**/
bool keyboardPrintEightIT_OFF() {
    if (get_mods() & MOD_SHIFTS) {          // (
        unregister_code(KC_9);
    } else {                                // 8
        unregister_code(KC_8);
    }
    return false;
} /**/

bool keyboardPrintNineIT_ON() {             // 9)
    if (get_mods() & MOD_SHIFTS) {          // )
        register_code(KC_0);
    } else {                                // 9
        register_code(KC_9);
    }
    return false;
} /**/
bool keyboardPrintNineIT_OFF() {
    if (get_mods() & MOD_SHIFTS) {          // )
        unregister_code(KC_0);
    } else {                                // 9
        unregister_code(KC_9);
    }
    return false;
} /**/

bool keyboardPrintZeroIT_ON() {             // 0=
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // =
        clear_mods();
        register_code(KC_EQUAL);
        set_mods(modifier);
    } else {                                // 0
        register_code(KC_0);
    }
    return false;
} /**/
bool keyboardPrintZeroIT_OFF() {
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // =
        clear_mods();
        unregister_code(KC_EQUAL);
        set_mods(modifier);
    } else {                                // 0
        unregister_code(KC_0);
    }
    return false;
} /**/

bool keyboardPrintQuotIT_ON() {             // '?
    if (get_mods() & MOD_SHIFTS) {          // ?
        register_code(KC_SLSH);
    } else {                                // '
        register_code(KC_QUOT);
    }
    return false;
} /**/
bool keyboardPrintQuotIT_OFF() {            // '?
    if (get_mods() & MOD_SHIFTS) {          // ?
        unregister_code(KC_SLSH);
    } else {                                // '
        unregister_code(KC_QUOT);
    }
    return false;
} /**/

bool keyboardPrintIGraveIT_ON() {           // ì^
    if (get_mods() & MOD_SHIFTS) {          // ^
        register_code(KC_6);
    } else {                                // ì
        keyboardPrintIGrave();
    }
    return false;
} /**/
bool keyboardPrintIGraveIT_OFF() {          // ì^
    if (get_mods() & MOD_SHIFTS) {          // ^
        unregister_code(KC_6);
    }
    return false;
} /**/

bool keyboardPrintEGraveIT_ON() {           // èé[
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // é
        keyboardPrintEAcute();
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {     // [
            register_code(KC_LBRC);
        } else {
            keyboardPrintEGrave();          // è
        }
    }
    set_mods(modifier);
    return false;
} /**/
bool keyboardPrintEGraveIT_OFF() {          // èé[
    uint8_t modifier = get_mods();
    if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {         // [
        unregister_code(KC_LBRC);
    }
    return false;
} /**/

bool keyboardPrintPlusIT_ON() {             // +*]
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // *
        register_code(KC_LSHIFT);
        register_code(KC_8);
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // ]
            register_code(KC_RBRC);
        } else {                            // +
            register_code(KC_LSHIFT);
            register_code(KC_EQUAL);
        }
    }
    set_mods(modifier);
    return false;
} /**/
bool keyboardPrintPlusIT_OFF() {            // +*]
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // *
        unregister_code(KC_8);
        unregister_code(KC_LSHIFT);
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // ]
            unregister_code(KC_RBRC);
        } else {                            // +
            unregister_code(KC_EQUAL);
            unregister_code(KC_LSHIFT);
        }
    }
    return false;
} /**/

bool keyboardPrintUGraveIT_ON() {           // ù§
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // §
        keyboardPrintSection1();
    } else {                                // ù
        keyboardPrintUGrave();
    }
    set_mods(modifier);
    return false;
} /**/

bool keyboardPrintOGraveIT_ON() {           // òç@
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // ç
        keyboardPrintCedilla();
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // @
            register_code(KC_LSHIFT);
            register_code(KC_2);
        } else {
            keyboardPrintOGrave();          // ò
        }
    }
    set_mods(modifier);
    return false;
} /**/
bool keyboardPrintOGraveIT_OFF() {          // òç@
    uint8_t modifier = get_mods();
    if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // @
        unregister_code(KC_2);
        unregister_code(KC_LSHIFT);
    }
    return false;
} /**/

bool keyboardPrintAGraveIT_ON() {           // à°#
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // °
        keyboardPrintDegree();
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // #
            register_code(KC_LSHIFT);
            register_code(KC_3);
        } else {
            keyboardPrintAGrave();          // à
        }
    }
    set_mods(modifier);
    return false;
} /**/
bool keyboardPrintAGraveIT_OFF() {          // à°#
    uint8_t modifier = get_mods();
    if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // #
        unregister_code(KC_3);
        unregister_code(KC_LSHIFT);
    }
    return false;
} /**/

bool keyboardPrintCommaIT_ON() {            // ,;<
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // ;
        register_code(KC_SCLN);
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // <
            register_code(KC_LSHIFT);
            register_code(KC_COMMA);
        } else {                            // ,
            register_code(KC_COMMA);
        }
    }
    set_mods(modifier);
    return false;
} /**/
bool keyboardPrintCommaIT_OFF() {           // ,;<
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // ;
        unregister_code(KC_SCLN);
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // <
            unregister_code(KC_COMMA);
            unregister_code(KC_LSHIFT);
        } else {                            // ,
            unregister_code(KC_COMMA);
        }
    }
    return false;
} /**/

bool keyboardPrintDotIT_ON() {              // .:>
    uint8_t modifier = get_mods();
    clear_mods();
    if (modifier & MOD_SHIFTS) {            // :
        register_code(KC_LSHIFT);
        register_code(KC_SCLN);
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // >
            register_code(KC_LSHIFT);
            register_code(KC_DOT);
        } else {                            // .
            register_code(KC_DOT);
        }
    }
    set_mods(modifier);
    return false;                           
} /**/
bool keyboardPrintDotIT_OFF() {             // .:>
    uint8_t modifier = get_mods();
    if (modifier & MOD_SHIFTS) {            // :
        unregister_code(KC_SCLN);
        unregister_code(KC_LSHIFT);
    } else {
        if (modifier & MOD_BIT(KC_RALT) || (modifier & MOD_BIT(KC_LCTRL) && modifier & MOD_BIT(KC_LALT))) {    // >
            unregister_code(KC_DOT);
            unregister_code(KC_LSHIFT);
        } else {                            // .
            unregister_code(KC_DOT);
        }
    }
    return false;                           
} /**/

bool keyboardPrintMinusIT_ON() {            // -_
    if (get_mods() & MOD_SHIFTS) {          // _
        register_code(KC_LSHIFT);
        register_code(KC_MINUS);
    } else {                                // -
        register_code(KC_MINUS);
    }
    return false;
} /**/
bool keyboardPrintMinusIT_OFF() {           // -_
    if (get_mods() & MOD_SHIFTS) {          // _
        unregister_code(KC_MINUS);
        unregister_code(KC_LSHIFT);
    } else {                                // -
        unregister_code(KC_MINUS);
    }
    return false;
} /**/


bool keyboardPrintAAcute() {
    uint8_t modifiers = get_mods();         // Key modifiers (ALT,SHIFT,CTRL,...), used in process_record_user()
    if (modifiers & MOD_BIT(KC_RALT)) {     // áÁ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {       // Á (A acute uppercase)
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_3)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "A"); break;
                case LINUX:
                default:    LINUX_UNICODE("c1");
            }
        } else {                            // á
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_5)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "a"); break;
                case LINUX:
                default:    LINUX_UNICODE("e1");
            }
        }
        set_mods(modifiers);
        return false;
    }
    return true;
} /**/

bool keyboardPrintEAcute() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) {     // éÉ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {       // É
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_1)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "E"); break;
                case LINUX:
                default:    LINUX_UNICODE("c9");
            }
        } else {                            // é
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_3)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "e"); break;
                case LINUX:
                default:    LINUX_UNICODE("e9");
            }
        }
        set_mods(modifiers);
        return false;
    }
    return true;
} /**/

bool keyboardPrintIAcute() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) {     // íÍ
        clear_mods();                       // Í
        if (modifiers & MOD_SHIFTS) {
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_5)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "I"); break;
                case LINUX:
                default:    LINUX_UNICODE("cd");
            }
        } else {                            // í
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_7)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "i"); break;
                case LINUX:
                default:    LINUX_UNICODE("ed");
            }
        }
        set_mods(modifiers);
        return false;
    }
    return true;
} /**/

bool keyboardPrintOAcute() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) {     // óÓ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {       // Ó
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_1)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "O"); break;
                case LINUX:
                default:    LINUX_UNICODE("d3");
            }
        } else {                            // ó
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_3)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "o"); break;
                case LINUX:
                default:    LINUX_UNICODE("f3");
            }
        }
        set_mods(modifiers);
        return false;
    }
    return true;
} /**/

bool keyboardPrintUAcute() {
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_BIT(KC_RALT)) {     // úÚ
        clear_mods();
        if (modifiers & MOD_SHIFTS) {       // Ú
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_8)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "U"); break;
                case LINUX:
                default:    LINUX_UNICODE("da");
            }
        } else {                            // ú
            switch (osCurrent()) {
                case WIN:   WINDOWS_CODE(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_0)); break;
                case MACOS: MACOS_CODE(SS_LALT("e") "u"); break;
                case LINUX:
                default:    LINUX_UNICODE("fa");
            }
        }
        set_mods(modifiers);
        return false;
    }
    return true;
} /**/
