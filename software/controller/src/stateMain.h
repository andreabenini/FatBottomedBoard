#ifndef STATEMAIN_H
#define STATEMAIN_H
#include <Arduino.h>            // Arduino.h should always be below usb_private.h
#include <TFT.h>

#include "defines.h"
#include "main.h"


void mainPage();
void mainLoop();
void mainAction(byte Action);
void mainNumLock(byte Active);
void mainCapsLock(byte Active);
void mainCompose();

#endif
