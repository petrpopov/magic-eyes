#include <Adafruit_NeoPixel.h>
#include "NeoPattern.h"

#define PIN_LEFT 0
#define PIN_RIGHT 1
#define LED_COUNT 16
#define BRIGTHNESS 30

NeoPattern *leftRing;
NeoPattern *rightRing;

//callbacks
void leftRingComplete() {
  //change some parameters on complete like Interval or Pattern or Direction
}

void rightRingComplete() {
  
}

void setup() {
  leftRing = new NeoPattern(LED_COUNT, PIN_LEFT, NEO_GRB + NEO_KHZ800, BRIGTHNESS, &leftRingComplete);
  rightRing = new NeoPattern(LED_COUNT, PIN_RIGHT, NEO_GRB + NEO_KHZ800, BRIGTHNESS, &leftRingComplete);

  leftRing->begin();
  rightRing->begin();

  leftRing->RainbowCycle(20);
  rightRing->RainbowCycle(20, REVERSE);
}

//main loop
void loop() {
  leftRing->Update();
  rightRing->Update();

  //read some buttons
  //and change parameters or patterns on press
}

