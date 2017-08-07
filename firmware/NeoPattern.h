#ifndef neopattern_h
#define neopattern_h

#include <Adafruit_NeoPixel.h>

// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, FADE };
// Patern directions supported:
enum  direction { FORWARD, REVERSE };

class NeoPattern : public Adafruit_NeoPixel {
  
  public:
    NeoPattern(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)());
    NeoPattern(uint16_t pixels, uint8_t pin, uint8_t type, uint8_t brightness, void (*callback)());
    
    pattern  ActivePattern;  // which pattern is running
    direction Direction;     // direction to run the pattern

    unsigned long Interval;   // milliseconds between updates
    
    uint32_t Color1, Color2;  // What colors are in use
    uint16_t TotalSteps;  // total number of steps in the pattern
    uint16_t Index;  // current step within the pattern

    void Update();
    void RainbowCycle(uint8_t interval, direction dir = FORWARD);
    void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD);
    
  private:
    uint8_t Brightness;
    unsigned long lastUpdate; // last update of position
    
    //update methods
    void (*OnComplete)();  // Callback on completion of pattern
    void Increment();

    //pattern updates
    void RainbowCycleUpdate();
    void FadeUpdate();
    
    //direction
    void Reverse();
     
    //color functions
    uint8_t Red(uint32_t color);
    uint8_t Green(uint32_t color);
    uint8_t Blue(uint32_t color);
    uint32_t DimColor(uint32_t color);
    void ColorSet(uint32_t color);
    uint32_t Wheel(byte WheelPos);
};

#endif
