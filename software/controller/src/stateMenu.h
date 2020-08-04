#ifndef STATEMENU_H
#define STATEMENU_H
#include <Arduino.h>            // Arduino.h should always be below usb_private.h

#include "defines.h"
#include "display.h"
#include "main.h"


void menuPage();
void menuShow();
void menuAction(byte Action);
void menuSelect(byte Choice);
void VolumeControl(byte Action);


#endif
