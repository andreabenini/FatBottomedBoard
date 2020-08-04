#ifndef DATA_H
#define DATA_H
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

#include "main.h"
#include "defines.h"


byte configRead(byte location,  byte defaultValue);
void configWrite(byte location, byte Value);

void cmdInit();
void cmdInitTeensy();
void cmdStart();
void cmdSerialRead();
void cmdSerial1Read();
void cmdDataProcess();
void cmdDataProcessTeensy();

#endif
