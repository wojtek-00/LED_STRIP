#include <Arduino.h>
#include <FastLED.h>
#include "parameters.h"

int brightness = 255;

CRGB leds[NUM_LEDS];  
int effectNumber;
int oldEffectNumber;

//################ MILLIS ###################
unsigned long previousMillis = 0;

//################ FLAGS ###################
bool increasing = true; 


int currentLED = 0;                       // Aktualny indeks LED
bool ledOn = false;    