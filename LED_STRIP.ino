#include "functions_led.h"
#include "parameters.h"
#include <FastLED.h> // Dodaj to




void setup() {
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS); // Inicjalizacja taśmy
  FastLED.setBrightness(BRIGHTNESS); // Ustawienie jasności
  pinMode(RELY_PIN, OUTPUT);
  digitalWrite(RELY_PIN, LOW);
  delay(100);
}

void loop() {
  CRGB colour = CRGB::White; // Poprawna deklaracja koloru

  //plainColour(colour);
  //breathingEffect(15, colour); // Wywołanie funkcji efektu oddychania
  rainbowWave(20); // Wywołanie efektu tęczowego
  //twinkleEffect(30, colour);    // Efekt skręcania
  //colorBurstEffect(3000); // Efekt wybuchu kolorów
  //waveEffect(100, colour);       // Efekt fali
  //plainColour(colour);
}

