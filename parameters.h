// parameters.h
#ifndef PARAMETERS
#define PARAMETERS

#define LED_PIN     2     // Pin to control LED
#define NUM_LEDS    50    // Amount od LEDs
#define BRIGHTNESS  255   // Max brightness of LED (255 max)
#define RELY_PIN    4     // Pin to control rely
#define SLAVE_ADDR   8     // slave addres


extern volatile int receivedValue; // Przechowuje wartość odebraną przez I2C
extern volatile bool newData;  // Flaga oznaczająca nowe dane


extern int brightness;
extern int dimmVal;

extern CRGB leds[NUM_LEDS];
extern int effectNumber;
extern int oldEffectNumber;

extern String colourName;
extern CRGB LED_colour;

extern int actualColour[3];
//################ FUNCTIONS ###################

//breath
extern int breathBrightness;
extern bool increasing;   //flag for breatch

//waveEffect
extern int LEDDistance;
extern int LEDAmount;

//twinkleEffect
extern int currentLED;                       // Aktualny indeks LED


//################ MILLIS ###################
extern unsigned long previousMillis;


//################ FLAGS ###################
extern bool isOnFlag;

extern bool isOnByMotion;



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
