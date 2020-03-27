// System libs
#include <TFT.h>
#include <SPI.h>

// Project defines
#define cs              9
#define dc              10
#define reset           8

#define encoderSW       2
#define encoderA        4
#define encoderB        3

#define XPOS            30
#define YPOS            50
#define RECT_X          XPOS - 15
#define RECT_Y          YPOS - 15
#define WIDTH           70
#define HEIGHT          50
#define COLOR           127
#define COLOR_BUTTON    20

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, reset);
char Text[20];
// Encoder last state
int encoderState;
// int encoderCurrentStatus;
int encoderCounter = 0;
int encoderButton = HIGH;

void setup() {
    TFTscreen.begin();
    // TFT display
    TFTscreen.background(0, 0, 0);        // clear the screen with a black background
    TFTscreen.setTextSize(3);             // set the text size
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.fillRect(RECT_X, RECT_Y, WIDTH, HEIGHT, COLOR);

    // Rotary encoder
    pinMode(encoderA,   INPUT_PULLUP);
    pinMode(encoderB,   INPUT_PULLUP);
    pinMode(encoderSW,  INPUT_PULLUP);
    encoderState = digitalRead(encoderA);
    sprintf(Text, "%d", encoderCounter);
    TFTscreen.text(Text, XPOS, YPOS);
}

void loop() {
    // Encoder current status
    int status = digitalRead(encoderA);
    if (status != encoderState) {
        if (digitalRead(encoderB) != status) {
            encoderCounter++;
        } else {
            encoderCounter--;
        }
        sprintf(Text, "%d", encoderCounter);
        TFTscreen.fillRect(RECT_X, RECT_Y, WIDTH, HEIGHT, COLOR);
        TFTscreen.text(Text, XPOS, YPOS);
        encoderState = status;
    }

    // Encoder button
    int button = digitalRead(encoderSW);
    if (button != encoderButton) {
        TFTscreen.fillRect(100, RECT_Y, 40, HEIGHT, button==HIGH? 0: COLOR_BUTTON);
        encoderButton = button;
    }
}
