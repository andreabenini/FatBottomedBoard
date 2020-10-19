#include "data.h"
byte cmdMode, detectEOT;
byte bufferPos;
byte bufferTeensyPos;

extern File fileMacro;
extern char cmdBuffer[BUFFERMAX];
extern char cmdBuffer1[BUFFERTEENSY];


byte configRead(byte location, byte defaultValue) {
    byte result = EEPROM.read(location);
    if (result == 0xFF) {
        EEPROM.write(location, defaultValue);
        return defaultValue;
    }
    return result;
} /**/


void configWrite(byte location, byte Value) {
    EEPROM.write(location, Value);
} /**/


void cmdStart() {
    cmdMode = DATAMODE_NONE;
    cmdInit();
} /**/


void cmdInitTeensy() {
    memset(cmdBuffer1, 0x00, BUFFERTEENSY);
    bufferTeensyPos = 0;
} /**/


void cmdInit() {
    memset(cmdBuffer, 0x00, BUFFERMAX);
    bufferPos = detectEOT = 0;
} /**/


void cmdSerialRead() {
    byte Incoming = Serial.read();
    switch (Incoming) {
    case '\r':
        break;
    case '\n':
        cmdDataProcess();
        return;
    default:
        if (bufferPos < BUFFERMAX) {
            cmdBuffer[bufferPos] = Incoming;
            bufferPos++;
        } else {
            cmdStart();
        }
        break;
    }
} /**/


void cmdSerial1Read() {
    byte Incoming = Serial1.read();
    switch (Incoming) {
    case '\r':
        break;
    case '\n':
        cmdDataProcessTeensy();
        return;
    default:
        if (bufferTeensyPos < BUFFERTEENSY) {
            cmdBuffer1[bufferTeensyPos] = Incoming;
            bufferTeensyPos++;
        } else {
            cmdInitTeensy();
        }
        break;
    }
} /**/


void cmdDataProcess() {
    switch (cmdMode) {
    case DATAMODE_NONE:
        if (!strcmp_P(cmdBuffer, (PGM_P) F("PUT MACRO"))) {
            if (stateGet() != STATUS_REMOTECONFIG) {
                stateSet(STATUS_REMOTECONFIG);
            }
            cmdInit();
            cmdMode = DATAMODE_MACRO;
            // Create/Open [FILE_MACRO] file (see defines.h)
            if (SD.exists(FILE_MACRO)) {
                SD.remove(FILE_MACRO);
            }
            fileMacro.close();
            fileMacro = SD.open(FILE_MACRO, FILE_WRITE);
        }
        break;
    case DATAMODE_MACRO:
        if (bufferPos==0) {                 // Empty line, detect EOT on command
            if (detectEOT==0) {
                detectEOT = 1;
            } else {
                fileMacro.close();          // close [FILE_MACRO]
                stateSet(STATUS_NONE);
                cmdStart();
            }
        } else {                            // Something to write on macro file
            fileMacro.println(cmdBuffer);
            cmdInit();
        }
        break;
    };
} /**/


void cmdDataProcessTeensy() {
    switch (cmdBuffer1[0]) {
    case 'l':                               // Change current layout on display
        layout(cmdBuffer1+1);
        break;
    case 'o':                               // Display new OS type (string: Linux, MacOS, Windows)
        osType(cmdBuffer1+1);
        break;
    }
    cmdInitTeensy();
} /**/
