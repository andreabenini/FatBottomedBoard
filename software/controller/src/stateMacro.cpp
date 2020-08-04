#include <usb_private.h>
#include "stateMacro.h"
extern TFT          display;
extern menuObject   menu;
extern File         fileMacro;

/**
 * Show macro page controls after changing the state
 */
void macroPage() {
    fileMacro = SD.open(FILE_MACRO, FILE_READ);
    menuInit(F("MACRO MODE"), 20, macroShow);
} /**/


/**
 * display macro menu, right after [macroPage]
 */
void macroShow() {
    char ch;
    char buffer[FONT1_MAXCOLS+1];
    byte lineShow = 1;

    memset(buffer, 0x00, sizeof(buffer));
    if (fileMacro) {
        fileMacro.seek(0);
        while (fileMacro.available()) {
            ch = fileMacro.read();
            switch (ch) {
            case '\n':
                lineShow = 1;
                memset(buffer, 0x00, sizeof(buffer));
                break;
            case '|':
                menu.itemShowStr(buffer);
                lineShow = 0;
                break;
            default:
                if (lineShow == 1) {
                    strncat(buffer, &ch, 1);
                    if (strlen(buffer) >= FONT1_MAXCOLS) {
                        lineShow = 0;
                    }
                }
                break;
            }
        }
    }
    menu.itemShow(F("EXIT"));
} /**/


/**
 * Do something with the current action
 */
void macroAction(byte Action) {
    switch (Action) {
        case ACTION_MACRO_LEFT:
            menu.moveUp();
            break;
        case ACTION_MACRO_RIGHT:
            menu.moveDown();
            break;
        case ACTION_MACRO_BUTTON:
            if (menu.itemGet() == menu.itemNum()-1) {   // Last option: exit
                fileMacro.close();
                stateSet(STATUS_NONE);
            } else {
                macroExecute(menu.itemGet());
            }
            break;
        case ACTION_CONTROL_LEFT:       // Rotary encoder movement [UP]
        case ACTION_CONTROL_RIGHT:      // Rotary encoder movement [DOWN]
        case ACTION_CONTROL_BUTTON:     // Button press
            fileMacro.close();
            stateSet(STATUS_NONE);
            break;
    }
} /**/


void macroExecute(unsigned int macroNumber) {
    char macro[MACROBUFFER_SIZE];
    fileMacro.seek(0);
    macroGetLineNumber(macroNumber, macro, MACROBUFFER_SIZE, 0);
    if (!strcmp_P(macro, (PGM_P) F(""))) {
        return;
    }
    macroCompile(macro);
    macroSendShow(1);
    Keyboard.print(macro);
    delay(1000);
    macroSendShow(0);
} /**/


void macroSendShow(byte SendShow) {
    if (SendShow == 1) {
        display.fillRect(0, 0, 160, 18, 0x001F);
    } else {
        display.fillRect(0, 0, 160, 18, 0xF522);
    }
    display.stroke(0, 0, 0);
    display.setTextSize(2);
    display.setCursor(20, 1);
    display.print(F("MACRO MODE"));
    display.stroke(255, 255, 255);
    display.setTextSize(1);
} /**/


void macroGetLineNumber(unsigned int macroNumber, char *buffer, unsigned int bufferlen, unsigned long currentLine) {
    byte firstChar = 0;
    char ch;
    memset(buffer, 0x00, bufferlen);
    while (fileMacro.available()) {
        ch = fileMacro.read();
        switch (ch) {
        case '\n':
            if (macroNumber != currentLine) {
                macroGetLineNumber(macroNumber, buffer, bufferlen, currentLine+1);
            }
            return;
        default:
            if (firstChar == 1) {
                if (strlen(buffer) < bufferlen-1) {
                    strncat(buffer, &ch, 1);
                }
            } else {
                if (ch == '|') {
                    firstChar = 1;
                }
            }
            break;
        }
    }
    memset(buffer, 0x00, bufferlen);        // Not found, return empty string
} /**/


void macroCompile(char *buffer) {
    char *p;
    p = buffer;
    while (*p != 0x00) {
        if (*p == '\\') {
            if (*(p+1) == '\\') {           // "\\" -> "\"
                memmove(p, p+1, strlen(p));
            } else {                        // "\0D" -> "\n"    (hexdump to real char)
                macroDecodeHex(p);
            }
        }
        p++;
    }
} /**/


void macroDecodeHex(char *pointer) {
    char hexString[3];
    // Skip leading '\' and copy next two chars ("\0D" -> "0D") into [hexString]
    if (strlen(pointer+1) < 2) {
        return;
    }
    memcpy(hexString, pointer+1, 2);
    hexString[2] = '\0';
    // Decode hex string into char
    *pointer = strtol(hexString, NULL, 16);
    // Move remaining part of the string
    memmove(pointer+1, pointer+3, strlen(pointer+3)+1);     // Move trailing \0 as well
} /**/
