#ifndef FUNCTIONS_LED  // Sprawdza, czy MY_FUNCTIONS_H nie jest zdefiniowane
#define FUNCTIONS_LED  // Definiuje MY_FUNCTIONS_H
#include <FastLED.h>

void ledOff();

//just a plain colour
void plainColour(CRGB colour_fun);

//brighter and darker
void breathingEffect(int wait, CRGB colour_fun);

//colours chanching along the strip
void rainbowWave(int wait);

// changing colours on the entire LED Strip
void colorsAlerating(int interval);

//colour running along the strip
void twinkleEffect(int wait, CRGB colour_fun);

//a lot of random colours
void colorBurstEffect(int wait);

//
void waveEffect(int wait);

CRGB Wheel(byte WheelPos);


void turnOn(int wait, CRGB colour_fun, int maxBrightness);

void turnOff(int wait, CRGB colour_fun);

void chooseColour();

void dimmFunction();


#endif