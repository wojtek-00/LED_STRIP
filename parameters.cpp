#include <Arduino.h>
#include <FastLED.h>
#include "parameters.h"

//################ GENERAL ###################
volatile int receivedValue = 0; // Przechowuje wartość odebraną przez I2C
volatile bool newData = false;  // Flaga oznaczająca nowe dane



int brightness = 255;
int dimmVal = 10;



CRGB leds[NUM_LEDS];  
int effectNumber;
int oldEffectNumber;

String colourName;
CRGB LED_colour;

int actualColour[3];
//################ FUNCTIONS ###################

//breath
int breathBrightness = 255;
bool increasing = true;

//waveEffect
int LEDDistance = 4;
int LEDAmount = 3;

//trinkleEffect
int currentLED = 0;                       // Aktualny indeks LED 

//################ MILLIS ###################
unsigned long previousMillis = 0;


//################ FLAGS ###################
bool isOnFlag;

bool isOnByMotion = false;

bool isOnTotalFlag = false;

bool turnOffForWave = false;




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
    {20, "lime", 50, 205, 50},             // Limonkowy
    {21, "white", 255, 255, 255},         // Biały
    {23, "turquoise", 64, 224, 208}, 
    {27, "teal", 0, 128, 128},             // Morski
    {29, "olive", 128, 128, 0},            // Oliwkowy
    {28, "coral", 255, 127, 80}, 
};
