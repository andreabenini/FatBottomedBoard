#ifndef STATEMACRO_H
#define STATEMACRO_H
#include <Arduino.h>            // Arduino.h should always be below usb_private.h
#include <TFT.h>

#include "main.h"
#include "display.h"


void macroPage();
void macroShow();
void macroAction(byte Action);
void macroExecute(unsigned int macroNumber);
void macroGetLineNumber(unsigned int macroNumber, char *buffer, unsigned int bufferlen, unsigned long currentLine);
void macroCompile(char *buffer);
void macroSendShow(byte SendShow);
void macroDecodeHex(char *pointer);

#endif
