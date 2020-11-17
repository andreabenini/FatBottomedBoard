#include <stdio.h>
#include <stdlib.h>

void main() {
    char pid[20];

    sprintf(pid, "0x0123");

    int result = (int)strtol(pid, NULL, 16);

    printf("Hello %s [%d] %04x\n", pid, result, result);
}
