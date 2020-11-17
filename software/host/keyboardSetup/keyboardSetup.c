/*
 * keyboardSetup command line utility. Works on any POSIX system (Unix/Mac/Win)
 *
 * Linux    gcc and you're ready to go
 * Mac      Make sure you have Xcode installed, gcc is fine
 * Windows  Try MinGW to get GCC. Zero tests here...
 */
#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // for usleep()
#include <signal.h>

// Local libs
#include "com.h"
#include "utility.h"


/**
 * MAIN
 */
int main(int argc, char *argv[]) {
    int
        VID, PID,
        devicePort = -1;
    char
        deviceName[1024],
        fileName[1024];

    // Parsing input
    signal(SIGINT, intHandler);
    programParseArguments(argc, argv, &VID, &PID, fileName, sizeof(fileName));

    // Scanning USB bus
    usbScan(VID, PID, deviceName, (unsigned char)sizeof(deviceName));

    // Port Init
    devicePort = portInit(deviceName, DEFAULT_SPEED);
    if (devicePort < 0) {
        fprintf(stderr, "\nERROR: Device %s\n", deviceName);
        errorExit("Cannot open port");
    }
    #ifdef VERBOSE_MODE
        fprintf(stdout, "Opening port %s\n", deviceName);
    #endif
    portFlush(devicePort);

    // Write MACRO file to device
    FILE *fHandler = fopen(fileName, "r");
    if (fHandler==NULL) {
        errorExit("Cannot read macro file");
    }
    if (portWrite(devicePort, "PUT MACRO\n") != 0) {
        errorExit("Cannot send 'MACRO' command");
    }
    usleep(COMMAND_DELAY);
    char line[1024];
    while (fgets(line, sizeof(line), fHandler)) {
        if (portWrite(devicePort, line) != 0) {
            fprintf(stderr, "\nERROR: Cannod send line >%s<\n", line);
            errorExit("Cannot send 'MACRO' file");
        }
        fprintf(stdout, ".");
        fflush(stdout);
        usleep(COMMAND_DELAY);
    }
    fclose(fHandler);
    // Close everything and go home
    if (portWrite(devicePort, "\n\n") != 0) {
        errorExit("Error while closing file\n");
    }
    portClose(devicePort);
    printf("\nConfiguration completed\n\n");
    exit(EXIT_SUCCESS);
} /**/
