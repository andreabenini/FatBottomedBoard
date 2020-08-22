#ifndef STATEBACKLIGHT_H
#define STATEBACKLIGHT_H
#include <Arduino.h>            // Arduino.h should always be below usb_private.h

#include "defines.h"
#include "display.h"
#include "main.h"
#include "data.h"


void backlightPage();
void backlightShow();
void backlightAction(byte Action);
void backlightSelect(byte Choice);
void backlightControl(byte Action);


#endif
