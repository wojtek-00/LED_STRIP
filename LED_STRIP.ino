#include "functions_led.h"
#include "parameters.h"
#include <FastLED.h> // Dodaj to



void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS); // Inicjalizacja taśmy
  FastLED.setBrightness(BRIGHTNESS); // Ustawienie jasności
  pinMode(RELY_PIN, OUTPUT);
  digitalWrite(RELY_PIN, LOW);
  oldEffectNumber = 1;
}

void loop() {
  effectNumber = 0;
  Serial.println("Number: ");
  if (Serial.available() > 0) {
    effectNumber = Serial.parseInt(); //
  }

  if (effectNumber == 0){

  } else if (effectNumber != oldEffectNumber){
    oldEffectNumber = effectNumber;
  }
  Serial.print("Current animation: ");
  Serial.println(oldEffectNumber);

  CRGB colour = CRGB::White; // Poprawna deklaracja koloru

  switch (oldEffectNumber) {
          case 1:
              ledOff();
              break;
          case 2:
              breathingEffect(15, colour); // Wywołanie funkcji efektu oddychania
              break;
          case 3:
              rainbowWave(20); // Wywołanie efektu tęczowego
              break;
          case 4:
              fill_solid(leds, NUM_LEDS, CRGB::Black);
              FastLED.show();
              twinkleEffect(30, colour); // Efekt skręcania
              break;
          case 5:
              colorBurstEffect(3000); // Efekt wybuchu kolorów
              break;
          case 6:
              waveEffect(100, colour); // Efekt fali
              break;
          case 7:
              plainColour(colour);
              break;
          default:
              ledOff();
              break;
      }
}

