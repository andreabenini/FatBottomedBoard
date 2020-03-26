// System libs
#include <TFT.h>
#include <SPI.h>

// Project defines
#define cs      9
#define dc      10
#define reset   8


// create an instance of the library
TFT TFTscreen = TFT(cs, dc, reset);


void setup() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);        // clear the screen with a black background
  TFTscreen.setTextSize(2);             // set the text size
}

void loop() {
  //generate a random color
  int redRandom   = random(0, 255);
  int greenRandom = random(0, 255);
  int blueRandom  = random(0, 255);
  
  // set a random font color
  TFTscreen.stroke(redRandom, greenRandom, blueRandom);
  
  // print Hello, World! in the middle of the screen
  TFTscreen.text("Hello World", 10, 57);
  
  // wait 200 miliseconds until change to next color
  delay(200);
}
