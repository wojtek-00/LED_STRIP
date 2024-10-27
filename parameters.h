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

extern String colourName;
extern CRGB LED_colour;

extern int actualColour[3];

extern int dimmVal;

//################ FUNCTIONS ###################

//breath
extern int breathBrightness;


//################ MILLIS ###################
extern unsigned long previousMillis;


//################ FLAGS ###################
extern bool increasing;   //flag for breatch
extern bool brightnessChange;   //flag for breatch
extern bool breathBrightChanged;


extern int currentLED;                       // Aktualny indeks LED
extern bool ledOn; 


//################ COLOURS ###################
extern const int colours_size;

struct Colour {
  int index;
  String name;
  int redValue;
  int greenValue;
  int blueValue;
};

extern Colour colours[];

#endif
