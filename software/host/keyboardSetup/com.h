#ifndef __COM_H__
#define __COM_H__

#include <stdint.h>   // Standard types 

#include "utility.h"


void usbScan(int vid, int pid, char *deviceName, unsigned char deviceNameLen);
int  portInit(const char *deviceName, int baud);
int  portClose(int fd);
int  portFlush(int fd);
int  portWrite(int fd, const char *str);
int  portWritebyte( int fd, uint8_t b);

int  serialport_read_until(int fd, char* buf, char until, int buf_max,int timeout);


#endif
