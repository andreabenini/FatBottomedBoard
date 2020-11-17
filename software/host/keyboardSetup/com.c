#include "com.h"

#if defined(OS_LINUX) || defined(OS_MACOSX)
#include <sys/ioctl.h>
#include <termios.h>            // POSIX terminal control definitions 
#elif defined(OS_WINDOWS)
#include <conio.h>
#endif
#include <stdio.h>              // Standard input/output definitions 
#include <string.h>             // String function definitions 
#include <unistd.h>             // UNIX standard function definitions 
#include <fcntl.h>              // File control definitions 
#include <errno.h>              // Error number definitions 

#include "hidapi.h"


void usbScan(int vid, int pid, char *deviceName, unsigned char deviceNameLen) {
    // Enumerate USB devices with proper VID:PID
    struct hid_device_info
        *deviceCurrent,
        *devices;
    strcpy(deviceName, "");
    devices = hid_enumerate(vid, pid);      // VID:PID // Detect USB with proper VID:PID
    deviceCurrent = devices;
    while (deviceCurrent) {
        // Detect proper hidraw device with that vid:pid
        if (deviceCurrent->interface_number == 2) {
            #ifdef VERBOSE_MODE             // Show its output
                printf("Device Found\n    Type            [%04hx:%04hx]\n    Path            %s\n    Serial Number  %ls", 
                        deviceCurrent->vendor_id, deviceCurrent->product_id, deviceCurrent->path, deviceCurrent->serial_number);
                printf("\n");
                printf("    Manufacturer    %ls\n", deviceCurrent->manufacturer_string);
                printf("    Product         %ls\n", deviceCurrent->product_string);
                printf("    Release         %hx\n", deviceCurrent->release_number);
                printf("    Interface       %d\n",  deviceCurrent->interface_number);
            #endif
            if (strlen(deviceCurrent->path) >= deviceNameLen) {
                strcpy(deviceName, deviceCurrent->path);
            } else {
                fprintf(stderr, "ERROR: %s\n", deviceCurrent->path);
                errorExit("Invalid hidraw device");
            }
        }
        deviceCurrent = deviceCurrent->next;
    }
    hid_free_enumeration(devices);
    if (!strcmp(deviceName, "")) {
        errorExit("Device not found");
    }
} /**/


// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1") and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.    returns valid fd, or -1 on error
int portInit(const char* deviceName, int baud) {
    struct termios toptions;
    int fd;
    fd = open(deviceName, O_RDWR | O_NONBLOCK );
    if (fd == -1)  {
        #ifdef VERBOSE_MODE
            fprintf(stderr, "portInit: Unable to open port\n");
        #endif
        return -1;
    }
    if (baud == 0) {                // When baud rate is not specified exit with the opened device, useful...
        return fd;                  // ...when dealing with /dev/hidraw devices (can't use tcgetattr() on that)
    }
    if (tcgetattr(fd, &toptions) < 0) {
        #ifdef VERBOSE_MODE
            fprintf(stderr, "portInit: Couldn't get term attributes\n");
        #endif
        return -1;
    }
    speed_t brate = baud; // let you override switch below if needed
    switch(baud) {
    case 4800:   brate=B4800;   break;
    case 9600:   brate=B9600;   break;
#ifdef B14400
    case 14400:  brate=B14400;  break;
#endif
    case 19200:  brate=B19200;  break;
#ifdef B28800
    case 28800:  brate=B28800;  break;
#endif
    case 38400:  brate=B38400;  break;
    case 57600:  brate=B57600;  break;
    case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;
    //toptions.c_cflag &= ~HUPCL;                           // disable hang-up-on-close to avoid reset

    toptions.c_cflag |= CREAD | CLOCAL;                     // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);            // turn off s/w flow ctrl
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);    // make raw
    toptions.c_oflag &= ~OPOST;                             // make raw

    // @see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 0;
    //toptions.c_cc[VTIME] = 20;
    
    tcsetattr(fd, TCSANOW, &toptions);
    if (tcsetattr(fd, TCSAFLUSH, &toptions) < 0) {
        #ifdef VERBOSE_MODE
            fprintf(stderr, "portInit: Couldn't set term attributes");
        #endif
        return -1;
    }
    return fd;
}


//
int portClose(int fd) {
    return close(fd);
} /**/


//
int portWriteByte(int fd, uint8_t b) {
    if (write(fd, &b, 1) != 1) {
        return -1;
    }
    return 0;
} /**/


//
int portWrite(int fd, const char *buffer) {
    size_t len = strlen(buffer);
    if (write(fd, buffer, len) != len) {
        return -1;
    }
    return 0;
} /**/


int portRead(int fd, const char *buffer) {
    return 0;
} /**/


//
int serialport_read_until(int fd, char* buf, char until, int buf_max, int timeout) {
    char b[1];  // read expects an array, so we give it a 1-byte array
    int i=0;
    do { 
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 1 * 1000 );  // wait 1 msec try again
            timeout--;
            if( timeout==0 ) return -2;
            continue;
        }
        #ifdef VERBOSE_MODE
            fprintf(stderr, "serialport_read_until: i=%d, n=%d b='%c'\n",i,n,b[0]);
        #endif
        buf[i] = b[0]; 
        i++;
    } while( b[0] != until && i < buf_max && timeout>0 );

    buf[i] = 0;  // null terminate the string
    return 0;
} /**/


//
int portFlush(int fd) {
    sleep(2);           // required to make flush work, for some reason TERMIO takes a while
    return tcflush(fd, TCIOFLUSH);
} /**/
