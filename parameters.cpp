#include <Arduino.h>
#include <FastLED.h>
#include "parameters.h"

int brightness = 255;

CRGB leds[NUM_LEDS];  
int effectNumber;
int oldEffectNumber;