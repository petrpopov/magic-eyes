#include "neopattern.h"

NeoPattern::NeoPattern(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)()) : Adafruit_NeoPixel(pixels, pin, type) {
  OnComplete = callback;
  Brightness = 255;
}

NeoPattern::NeoPattern(uint16_t pixels, uint8_t pin, uint8_t type, uint8_t brightness, void (*callback)()) : Adafruit_NeoPixel(pixels, pin, type) {
  OnComplete = callback;
  Brightness = brightness;
}

void NeoPattern::Update() {
  
  if((millis() - lastUpdate) > Interval) {
    
    lastUpdate = millis();
    
    switch(ActivePattern) {
      case RAINBOW_CYCLE: 
        RainbowCycleUpdate(); 
        break;  
      case FADE: 
        FadeUpdate(); 
        break; 
      default: break;
    }          
  }
}

void NeoPattern::Increment() {
  if (Direction == FORWARD) {
    Index++;
    if(Index >= TotalSteps) {
      Index = 0;
      if(OnComplete != NULL) {
        OnComplete();
      }
    }
  }
  else {
    --Index;
    if(Index <= 0) {
      Index = TotalSteps-1;
      if(OnComplete != NULL) {
        OnComplete();
      }
    }
  }
}

void NeoPattern::RainbowCycle(uint8_t interval, direction dir = FORWARD) {
  ActivePattern = RAINBOW_CYCLE;
  Interval = interval;
  TotalSteps = 255;
  Index = 0;
  Direction = dir;
}

void NeoPattern::RainbowCycleUpdate() {
  
  for(int i=0; i< numPixels(); i++) { 
    setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
  }

  setBrightness(Brightness);
  show();
  Increment();
}

void NeoPattern::Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD) {
  ActivePattern = FADE;
  Interval = interval;
  TotalSteps = steps;
  Color1 = color1;
  Color2 = color2;
  Index = 0;
  Direction = dir;
}

void NeoPattern::FadeUpdate() {
  uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;  
  uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
  uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
  ColorSet(Color(red, green, blue));

  setBrightness(Brightness);
  show();
  Increment();
}

//private utility methods
uint8_t NeoPattern::Red(uint32_t color) {
  return (color >> 16) & 0xFF;
}
 
    // Returns the Green component of a 32-bit color
uint8_t NeoPattern::Green(uint32_t color) {
  return (color >> 8) & 0xFF;
}
 
    // Returns the Blue component of a 32-bit color
uint8_t NeoPattern::Blue(uint32_t color) {
  return color & 0xFF;
}

uint32_t NeoPattern::DimColor(uint32_t color) {
  uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
  return dimColor;
}

void NeoPattern::ColorSet(uint32_t color) {
  
  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, color);
  }

  setBrightness(Brightness);
  show();
}

uint32_t NeoPattern::Wheel(byte WheelPos) {
  
  if(WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
   WheelPos -= 170;
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void NeoPattern::Reverse() {
  if (Direction == FORWARD) {
    Direction = REVERSE;
    Index = TotalSteps-1;
  }
  else {
    Direction = FORWARD;  
    Index = 0;
  }
}

