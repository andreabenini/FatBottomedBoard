#include "utility.h"

/**
 * CTRL+C Interrupt handler
 */
void intHandler(int dummy) {
    printf("\n\nCtrl+C detected.  Aborting program\n");
    fflush(stdout);
    exit(EXIT_SUCCESS);
} /**/


/**
 * Parsing program arguments
 */
void programParseArguments(int argc, char *argv[], int *VID, int *PID, char *fileName, unsigned int fileNameSize) {
    if (argc==1) {
        programUsage(argv[0]);
    }
    opterr = 0;                                                 // Avoid getopt_long() printf messages on errors or warnings
    *VID = *PID = 0;
    int option_index = 0;
    struct option loptions[] = {
        {"help",       no_argument,       0, 'h'},
        {"vid",        optional_argument, 0, 'v'},
        {"pid",        optional_argument, 0, 'p'},
        {"macro",      required_argument, 0, 'm'},
        {NULL,         0,                 0, 0}
    };
    char buffer[10];
    while (1) {
        switch (getopt_long(argc, argv, "hp:m:", loptions, &option_index)) {
        case 'h':                                               // Program help
            programUsage(argv[0]);
            break;
        case 'v':                                               // USB VID
            if (strlen(optarg) >= sizeof(buffer)) {
                errorExit("Invalid VID");
            }
            *VID = (int)strtol(optarg, NULL, 16);
            break;
        case 'p':                                               // USB PID
            if (strlen(optarg) >= sizeof(buffer)) {
                errorExit("Invalid PID");
            }
            *PID = (int)strtol(optarg, NULL, 16);
            break;
        case 'm':                                               // Macro file to send
            if (strlen(optarg) >= fileNameSize) {
                errorExit("Invalid filename");
            }
            strcpy(fileName, optarg);
            break;
        case -1:
            if (strcmp(fileName, "")==0) {
                errorExit("Missing parameters (see --help)");
            }
            if (*VID <= 0) {
                *VID = VID_DEFAULT;
            }
            if (*PID <= 0) {
                *PID = PID_DEFAULT;
            }
            return;
        default:
            programUsage(argv[0]);
        }
    }
} /**/


/**
 * Program Usage
 */
void programUsage(char *programName) {
    printf("\nUsage: %s -m <macroFile>\n"
    "\n"
    "Options:\n"
    "  -h, --help                 Print this help message\n"
    "  -v, --vid=VID              USB VID [default: 0x%04x]\n"
    "  -p, --pid=PID              USB PID [default: 0x%04x]\n"
    "  -m, --macro=macroFile      Send macroFile to the keyboard\n"
    "\n", programName, VID_DEFAULT, PID_DEFAULT);
    exit(EXIT_FAILURE);
} /**/


/**
 * ERROR EXIT - Exit program with errors
 * @see No need to terminate string [msg] with "\n"
 */
void errorExit(char* msg) {
    fprintf(stderr, "ERROR: %s\n\n", msg);
    exit(EXIT_FAILURE);
} /**/
