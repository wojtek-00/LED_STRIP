#include <Arduino.h>
#include <FastLED.h>
#include "parameters.h"

int brightness = 255;

CRGB leds[NUM_LEDS];  
int effectNumber;
int oldEffectNumber;

String colourName;
CRGB LED_colour;

int actualColour[3];

int dimmVal = 10;

//################ MILLIS ###################
unsigned long previousMillis = 0;

//################ FLAGS ###################
bool increasing = true;
bool brightnessChange = true; 


int currentLED = 0;                       // Aktualny indeks LED
bool ledOn = false;    


//################ COLOURS ###################
// Max size of the array with colours
const int colours_size = 14;

// array with colours
Colour colours[colours_size] = {
    {15, "red", 255, 0, 0},               // Czerwony
    {16, "green", 0, 255, 0},             // Zielony
    {17, "blue", 0, 0, 255},              // Niebieski
    {18, "yellow", 255, 255, 0},          // Żółty
    {19, "cyan", 0, 255, 255},            // Cyjan
    {20, "magenta", 255, 0, 255},         // Magenta
    {21, "white", 255, 255, 255},         // Biały
    {22, "orange", 255, 165, 0},          // Pomarańczowy
    {23, "purple", 128, 0, 128},          // Fioletowy
    {24, "pink", 255, 192, 203},          // Różowy
    {25, "brown", 165, 42, 42},           // Brązowy
    {26, "light blue", 173, 216, 230},    // Jasnoniebieski
    {27, "lime", 0, 255, 0},              // Limetka
    {28, "gold", 255, 215, 0}             // Złoty
};
