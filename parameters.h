// parameters.h
#ifndef PARAMETERS
#define PARAMETERS

#define LED_PIN     2     // Pin to control LED
#define NUM_LEDS    50    // Amount od LEDs
#define BRIGHTNESS  255   // Max brightness of LED (255 max)
#define RELY_PIN    4     // Pin to control rely

extern int brightness;

extern CRGB leds[NUM_LEDS];
extern int effectNumber;
extern int oldEffectNumber;

#endif
