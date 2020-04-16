/*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

  The circuit:
  - pushbutton attached from pin 4 to +5V
  - 10 kilohm resistor attached from pin 4 to ground

  created 24 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe
  modified 11 Nov 2013
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/

#include "Keyboard.h"

const int buttonPin = 4;                                // input pin for pushbutton
int previousButtonState = HIGH;                         // for checking the state of a pushButton
int counter = 0;                                        // button push counter

void setup() {
  pinMode(buttonPin, INPUT);                            // make the pushButton pin an input:
  Keyboard.begin();                                     // initialize control over the keyboard:
}

void loop() {
    int buttonState = digitalRead(buttonPin);           // read the pushbutton:
    // if the button state has changed, and it's currently pressed
    if ((buttonState != previousButtonState) && (buttonState == HIGH)) {
        counter++;                                      // increment the button counter
        Keyboard.print("You pressed the button ");      // type out a message
        Keyboard.print(counter);
        Keyboard.println(" times.");
    }
    previousButtonState = buttonState;                  // save the current button state for comparison next time:
} /**/
