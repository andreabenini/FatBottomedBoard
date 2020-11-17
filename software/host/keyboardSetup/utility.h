#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "com.h"

#define VERBOSE_MODE                // Comment it if you'd like to see fewer messages
#define DEFAULT_SPEED   0           // Default port speed [115200], there's no need on /dev/hidraw devs
#define COMMAND_DELAY   200         // ms. Delay between two command lines
#define VID_DEFAULT     0x08DE      // USB VID (Vendor: ???)
#define PID_DEFAULT     0xBABE      // USB PID (C0DE BABE.. oh yeah!)


void intHandler(int dummy);
void programParseArguments(int argc, char *argv[], int *VID, int *PID, char *fileName, unsigned int fileNameSize);
void programUsage();
void errorExit(char* msg);

#endif
