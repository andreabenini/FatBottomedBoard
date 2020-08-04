#ifndef STATESETUP_H
#define STATESETUP_H
#include <Arduino.h>            // Arduino.h should always be below usb_private.h

#include "defines.h"
#include "display.h"
#include "main.h"


void setupPage();
void setupShow();
void setupAction(byte Action);
void setupSelect(byte Choice);


#endif
