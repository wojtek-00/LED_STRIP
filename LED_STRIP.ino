#include "functions_led.h"
#include "parameters.h"
#include <FastLED.h> // Dodaj to
#include <Wire.h>

volatile int receivedValue = 0; // Przechowuje wartość odebraną przez I2C
volatile bool newData = false;  // Flaga oznaczająca nowe dane


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS); // Inicjalizacja taśmy
  FastLED.setBrightness(BRIGHTNESS); // Ustawienie jasności
  pinMode(RELY_PIN, OUTPUT);
  digitalWrite(RELY_PIN, LOW);
  oldEffectNumber = 1;                // defaulf OFF
  LED_colour = CRGB(255, 255, 255);   // default WHITE colour

  //Wire I2C
  Wire.begin(8);                  // Inicjalizacja jako Slave z adresem 8
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
  if (Serial.available() > 0) {
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
  } else if (effectNumber >= 15 && effectNumber < 35){
    // NUMBERS 15-35 for colours
    Serial.print("Farbe: ");
    int i;
    for (i = 0; i < colours_size; i++) {
      if (effectNumber == colours[i].index) {
        LED_colour = CRGB(colours[i].redValue, colours[i].greenValue, colours[i].blueValue);

        actualColour[0] = colours[i].redValue;
        actualColour[1] = colours[i].greenValue;
        actualColour[2] = colours[i].blueValue;

        break;
        }
    } 
    Serial.println(colours[i].name); 
  } else if (effectNumber >= 35 && effectNumber < 37){
    if (brightness >= 0 && brightness <= 255){
      //Dimm LED
      if (effectNumber == 35){
        brightness -= dimmVal;
        if (brightness < 0 ){
          brightness = 0;
        }

        Serial.print("Bright: ");
        Serial.println(brightness);

       //Brighter LED
      } else if (effectNumber == 36){
        Serial.println("Tu jestem");
        brightness += dimmVal;
        if (brightness > 255 ){
          brightness = 255;
        }
        Serial.print("Bright: ");
        Serial.println(brightness);
      
      }
    }
    breathBrightness = brightness;
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

