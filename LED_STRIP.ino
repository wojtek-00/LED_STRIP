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
      if (effectNumber == 35){
        brightness -= dimmVal;
        if (brightness < 0 ){
          brightness = 0;
        }

        Serial.print("Bright: ");
        Serial.println(brightness);

        
      
      /*
      if ((actualColour[0] != 0 && (LED_colour.r >= 0 && LED_colour.r < dimmVal)) || 
        (actualColour[1] != 0 && (LED_colour.g >= 0 && LED_colour.g < dimmVal)) || 
        (actualColour[2] != 0 && (LED_colour.b >= 0 && LED_colour.b < dimmVal))) {
          
          Serial.print("VALUE: (");
          Serial.print(LED_colour.r);
          Serial.print(", ");
          Serial.print(LED_colour.g);
          Serial.print(", ");
          Serial.print(LED_colour.b);
          Serial.println(")");

      } else {
        if (0 < LED_colour.r && LED_colour.r <= 255){
          LED_colour.r = LED_colour.r - dimmVal;
        }
        if (0 < LED_colour.g && LED_colour.g <= 255){
          LED_colour.g = LED_colour.g - dimmVal;
        }
        if (0 < LED_colour.b && LED_colour.b <= 255){
          LED_colour.b = LED_colour.b - dimmVal;
        }
        FastLED.show();

        Serial.print("VALUE: (");
        Serial.print(LED_colour.r);
        Serial.print(", ");
        Serial.print(LED_colour.g);
        Serial.print(", ");
        Serial.print(LED_colour.b);
        Serial.println(")");
      }*/
      } else if (effectNumber == 36){
        Serial.println("Tu jestem");
        brightness += dimmVal;
        if (brightness > 255 ){
          brightness = 255;
        }
        Serial.print("Bright: ");
        Serial.println(brightness);
      /*
      if ((actualColour[0] != 255 && (LED_colour.r > (255 - dimmVal) && LED_colour.r <= 255)) || 
        (actualColour[1] != 255 && (LED_colour.g > (255 - dimmVal) && LED_colour.g <= 255)) || 
        (actualColour[2] != 255 && (LED_colour.b > (255 - dimmVal) && LED_colour.b <= 255))) {
          
          Serial.print("VALUE: (");
          Serial.print(LED_colour.r);
          Serial.print(", ");
          Serial.print(LED_colour.g);
          Serial.print(", ");
          Serial.print(LED_colour.b);
          Serial.println(")");
        
      } else {
        if (0 < LED_colour.r && LED_colour.r < 255){
          LED_colour.r = LED_colour.r + dimmVal;
          
        }
        if (0 < LED_colour.g && LED_colour.g < 255){
          LED_colour.g = LED_colour.g + dimmVal;
        
        }
        if (0 < LED_colour.b && LED_colour.b < 255){
          LED_colour.b = LED_colour.b + dimmVal;
        }
        FastLED.show();

        Serial.print("VALUE: (");
        Serial.print(LED_colour.r);
        Serial.print(", ");
        Serial.print(LED_colour.g);
        Serial.print(", ");
        Serial.print(LED_colour.b);
        Serial.println(")"); 
      }*/
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

