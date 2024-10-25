#include "functions_led.h"
#include "parameters.h"
#include <FastLED.h> // Dodaj to



void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS); // Inicjalizacja taśmy
  FastLED.setBrightness(BRIGHTNESS); // Ustawienie jasności
  pinMode(RELY_PIN, OUTPUT);
  digitalWrite(RELY_PIN, LOW);
  oldEffectNumber = 1;                // defaulf OFF
  LED_colour = CRGB(255, 255, 255);   // default WHITE colour
}

void loop() {
  effectNumber = 0;
  
  if (Serial.available() > 0) {
    effectNumber = Serial.parseInt(); //
  }

  if (effectNumber == 0){
    // do nothing
  } else if (effectNumber <= 14){
    if (effectNumber != oldEffectNumber){
      oldEffectNumber = effectNumber;
      Serial.print("Current animation: ");
      Serial.println(oldEffectNumber);
    }
  } else if (effectNumber >= 15){
    Serial.print("Farbe: ");
    int i;
    for (i = 0; i < colours_size; i++) {
      if (effectNumber == colours[i].index) {
        LED_colour = CRGB(colours[i].redValue, colours[i].greenValue, colours[i].blueValue);
        break;
        }
    } 
    Serial.println(colours[i].name); 
  }
  


  // CASE 1 - 15 are for effects
  switch (oldEffectNumber) {
          case 1:
              ledOff();
              break;
          case 2:
              breathingEffect(15, LED_colour); // Wywołanie funkcji efektu oddychania
              break;
          case 3:
              rainbowWave(20); // Wywołanie efektu tęczowego
              break;
          case 4:
              twinkleEffect(30, LED_colour); // Efekt skręcania
              break;
          case 5:
              colorBurstEffect(1500); // Efekt wybuchu kolorów
              break;
          case 6:
              waveEffect(100, LED_colour); // Efekt fali
              break;
          case 7:
              plainColour(LED_colour);
              break;
          default:
              break;
      }
}

