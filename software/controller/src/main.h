#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include "defines.h"

byte stateGet();
void stateSet(byte newStatus);
void stateLoop();
void stateAction(byte Action);
void setup();
void loop();
void layout(const char *Layout);
void osType(char *osType);

#endif
