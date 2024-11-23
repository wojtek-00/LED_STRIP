#include "functions_led.h"
#include "parameters.h"
#include <FastLED.h> // Dodaj to
#include <Wire.h>



void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS); // Inicjalizacja taśmy
  FastLED.setBrightness(BRIGHTNESS); // Ustawienie jasności
  pinMode(RELY_PIN, OUTPUT);
  digitalWrite(RELY_PIN, HIGH);
  oldEffectNumber = 1;                // defaulf OFF
  LED_colour = CRGB(255, 255, 255);   // default WHITE colour
  isOnFlag = false;

  //Wire I2C
  Wire.begin(SLAVE_ADDR);                  // Inicjalizacja jako Slave z adresem 8
  Wire.onReceive(receiveEvent);   // Rejestracja funkcji obsługi odbioru danych
  Serial.begin(9600);             // Inicjalizacja portu szeregowego
}

void loop() {
  effectNumber = 0;
  
  if (newData) {                  // Sprawdzenie, czy przyszły nowe dane
    newData = false;              // Wyłączenie flagi po przetworzeniu danych
    Serial.print("Otrzymano: ");  // Wypisanie wartości na Serial Monitor
    Serial.println(receivedValue);
    if (receivedValue != 0){
      effectNumber = receivedValue;
    }
  }

/*
  if (Serial.available() > 0) {           // input in terminal
    effectNumber = Serial.parseInt(); //
  }
*/

  if (effectNumber == 0){
    // do nothing
  } else if (effectNumber <= 14){
    if (effectNumber != oldEffectNumber){
      oldEffectNumber = effectNumber;
      Serial.print("Current animation: ");
      Serial.println(oldEffectNumber);
    }

    // Turn on off
    if (oldEffectNumber == 1) {
      if (isOnFlag == false){
        digitalWrite(RELY_PIN, LOW);
        oldEffectNumber = 7;
        isOnFlag = true;
      } else if (isOnFlag == true) {
        oldEffectNumber = 1;
        isOnFlag = false;
        digitalWrite(RELY_PIN, HIGH);
      }
  }


  } else if (effectNumber >= 15 && effectNumber < 35 && isOnFlag == true){
    // NUMBERS 15-35 for colours
    
    chooseColour();

    
  } else if (effectNumber >= 35 && effectNumber < 37 && isOnFlag == true){
    // Number 35 Dimm, 36 Brighter
    dimmFunction();
  }

  
  if (isOnFlag == false) {
    if (oldEffectNumber == 1) {

    } else {
      oldEffectNumber = 0;
    }
  }

  // CASE 1 - 14 are for effects
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
              waveEffect(200, LED_colour); // Efekt fali
              break;
          case 7:
              plainColour(LED_colour);
              break;
          default:
              break;
      }
}



void receiveEvent(int howMany) {
  if (Wire.available()) {
    receivedValue = Wire.read();  // Odczyt danych z bufora
    newData = true;               // Ustawienie flagi, że przyszły nowe dane
  }
}

