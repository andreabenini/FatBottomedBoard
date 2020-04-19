/**
 * RawHID - Exchange data between ProMicro and Linux PC
 * 
 * @author  Ben
 * @date    2020-04-15
 * 
 * @see
 *          Credits to NicoHood for original source code https://github.com/NicoHood/HID/wiki/RawHID-API
 */
#include "HID-Project.h"

const int pinLed = LED_BUILTIN;

/**
 * Buffer to hold RawHID data. If host tries to send more data than this, it will respond with an error.
 * If the data is not read until the host sends the next data it will also respond with an error and the data will be lost.
 */
uint8_t rawhidData[255];

void setup() {
    pinMode(pinLed, OUTPUT);
    Serial.begin(115200);
    // Set the RawHID OUT report array. Feature reports are also (parallel) possible, see the other example for this.
    RawHID.begin(rawhidData, sizeof(rawhidData));
}

void loop() {
    // Send data to the host
    // if (!digitalRead(pinButton)) {
    //     digitalWrite(pinLed, HIGH);
    //     // Create buffer with numbers and send it
    //     uint8_t buffer[500];
    //     for (uint8_t i = 0; i < sizeof(buffer); i++) {
    //         buffer[i] = i;
    //     }
    //     RawHID.write(buffer, sizeof(buffer));
    //     // Simple debounce
    //     delay(300);
    //     digitalWrite(pinLed, LOW);
    // }
    // Check if there is new data from the RawHID device
    auto bytesAvailable = RawHID.available();
    if (bytesAvailable) {
        digitalWrite(pinLed, HIGH);
        // Mirror data via Serial
        while (bytesAvailable--) {
            Serial.println(RawHID.read());
        }
        digitalWrite(pinLed, LOW);
    }
} /**/
