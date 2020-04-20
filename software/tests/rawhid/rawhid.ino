/**
 * RawHID - This is just a simple echo program, each char received will be bounced back to host
 * 
 * @author  Ben
 * @date    2020-04-15
 * 
 * @see     NicoHood source API https://github.com/NicoHood/HID/wiki/RawHID-API
 */
#include "HID-Project.h"


/**
 * Buffer to hold RawHID data. If host tries to send more data than this, it will respond with an error.
 * If the data is not read until the host sends the next data it will also respond with an error and the data will be lost.
 */
uint8_t rawhidData[255];


void setup() {
    // Set the RawHID OUT report array. Feature reports are also (parallel) possible, see the other example for this.
    RawHID.begin(rawhidData, sizeof(rawhidData));
}


void loop() {
    // Check if there is new data from the RawHID device
    auto bytesAvailable = RawHID.available();
    if (bytesAvailable) {
        while (bytesAvailable--) {
            RawHID.write(RawHID.read());
        }
        delay(500);
    }
} /**/
