#include "functions_led.h"
#include "parameters.h"
#include <Arduino.h>

void ledOff(){
  FastLED.setBrightness(0);
  FastLED.show();
}

void plainColour(CRGB colour_fun) {
  FastLED.setBrightness(brightness);
  fill_solid(leds, NUM_LEDS, colour_fun); // Set the colour
  FastLED.show(); // Show the colour
}

void breathingEffect(int interval, CRGB colour_fun) {
  unsigned long currentMillis = millis();  // Read the current time
  
  // Check if the time since the last brightness update has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the previous time

    // Update the LED brightness
    if (increasing) {
      breathBrightness++;
      if (breathBrightness >= brightness) {
        increasing = false;  // When we reach maximum brightness, change direction
      }
    } else {
      breathBrightness--;
      if (breathBrightness <= 25) {
        increasing = true;   // When we reach minimum brightness, change direction
      }
    }


    // Set the brightness and display the colour
    FastLED.setBrightness(breathBrightness);
    fill_solid(leds, NUM_LEDS, colour_fun); // Set colour to the specified colour
    FastLED.show();
  }
}

void rainbowWave(int interval) {
   unsigned long currentMillis = millis();  // Read the current time
  
  // Check if the time since the last update has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the previous time

    static uint16_t j = 0;
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = Wheel((i + j) & 255);
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
    j += 1;
  }
}

void colorsAlerating(int interval) {
   unsigned long currentMillis = millis();  // Read the current time
  
  // Check if the time since the last update has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the previous time

  static int j = 0;
  LED_colour = Wheel(j & 255);

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = LED_colour;
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
    j += 1;
  }
}


void twinkleEffect(int wait, CRGB colour_fun) {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= wait) {
    previousMillis = currentMillis;

    if (currentLED == 0){
      leds[currentLED] = colour_fun;
      leds[(NUM_LEDS / 2) + currentLED] = colour_fun;

    } else {
      leds[currentLED] = colour_fun;
      leds[currentLED - 1] = CRGB::Black;

      leds[(NUM_LEDS / 2) + currentLED] = colour_fun;
      leds[(NUM_LEDS / 2) + currentLED - 1] = CRGB::Black;
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
    currentLED++;
    
    if (currentLED >= NUM_LEDS / 2) {
      leds[NUM_LEDS - 1] = CRGB::Black;
      leds[(NUM_LEDS / 2) - 1] = CRGB::Black;
      currentLED = 0;
    }
  }
}

void colorBurstEffect(int interval) {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(random(255), random(255), random(255));
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
  }
}

// Wave walking around the LED Strip
void waveEffect(int interval) {
  unsigned long currentMillis = millis();

  if (turnOffForWave == false) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.setBrightness(255);
    FastLED.show();
    turnOffForWave = true;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.println("Function Wave");
    static int waveIndex = 0;
    static bool modeFlag = false;
    static int increaseIndex = 40;

    CRGB tempLedColour = CRGB(0, 0, 0);

    int redValue = LED_colour.r;
    int greenValue = LED_colour.g;
    int blueValue = LED_colour.b;

    static int tempRedValue = 0;
    static int tempGreenValue = 0;
    static int tempBlueValue = 0;

    waveIndex = waveIndex % NUM_LEDS;

    if (modeFlag == false) {
      leds[waveIndex] = CRGB(tempRedValue, tempGreenValue, tempBlueValue);
      FastLED.show();

      tempRedValue += increaseIndex;
      tempGreenValue += increaseIndex;
      tempBlueValue += increaseIndex;

      if (tempRedValue >= 255 || tempGreenValue >= 255 || tempBlueValue >= 255) {
        tempRedValue = 255;
        tempGreenValue = 255;
        tempBlueValue = 255;
        modeFlag = true;
      }
      Serial.println(tempRedValue);
      Serial.println(modeFlag);
    }

    if (modeFlag == true) {
      leds[waveIndex] = CRGB(tempRedValue, tempGreenValue, tempBlueValue);
      FastLED.show();

      tempRedValue -= increaseIndex;
      tempGreenValue -= increaseIndex;
      tempBlueValue -= increaseIndex;

      if (tempRedValue <= 0 || tempGreenValue <= 0 || tempBlueValue <= 0) {
        tempRedValue = 0;
        tempGreenValue = 0;
        tempBlueValue = 0;
        leds[waveIndex] = CRGB(tempRedValue, tempGreenValue, tempBlueValue);
        FastLED.show();
        modeFlag = false;
        waveIndex += 1;
      }
    }
  }
}


// Generate the colours
CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3); // Move from red to green
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3); // Move from green to blue
  } else {
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0); // Move from blue to red
  }
}


void chooseColour(){
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
}

void dimmFunction(){
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

void turnOn(int wait, CRGB colour_fun, int maxBrightness) { 
  Serial.println("Turn on function ");
  LED_colour = colour_fun;
  digitalWrite(RELY_PIN, LOW);

  for (int tempBrightness = 0; tempBrightness <= maxBrightness; tempBrightness = tempBrightness + 5) {
    FastLED.setBrightness(tempBrightness);
    fill_solid(leds, NUM_LEDS, colour_fun); // Set the colour
    FastLED.show(); // Show the colour
    brightness = tempBrightness;
    delay(wait);
  }
  oldEffectNumber = 7;
  isOnFlag = true;
}

void turnOff(int wait, CRGB colour_fun) {
  Serial.println("Turn off function ");

  for (int tempBrightness = brightness; tempBrightness >= 0; tempBrightness = tempBrightness - 5) {
    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, colour_fun); // Set the colour
    FastLED.show(); // Show the colour
    delay(wait);
    brightness = tempBrightness;
  }
  if (brightness != 0) {
    brightness = 0;
    FastLED.setBrightness(brightness);
  }

  LED_colour = colour_fun;
  digitalWrite(RELY_PIN, HIGH);
  isOnFlag = false;
}

CRGB changeColour(CRGB colour_fun) {
  CRGB tempLedColour = LED_colour;

  int dimmConst = 10;
  static bool matchFlag[3] = {false, false, false};
  static int calculationInd[3]; // target > temp -> temp++; target < temp -> temp--; target == temp -> nothing
  static int tempColour[3];
  static int targetColour[3];

  for (int i = 0; i < 3; i++) {
    matchFlag[i] = false;
  }

  tempColour[0] = tempLedColour.r;
  tempColour[1] = tempLedColour.g;
  tempColour[2] = tempLedColour.b;

  targetColour[0] = colour_fun.r;
  targetColour[1] = colour_fun.g;
  targetColour[2] = colour_fun.b;

  Serial.println("Insife Fun");


  while (!(matchFlag[0] && matchFlag[1] && matchFlag[2])) {
    for (int i = 0; i < 3; i++) {
      if (!matchFlag[i]) {
        if (tempColour[i] > targetColour[i]) {
          tempColour[i] -= dimmConst;

          if (tempColour[i] <= targetColour[i]) {
            tempColour[i] = targetColour[i];
            matchFlag[i] = true;
          }
        } else if (tempColour[i] < targetColour[i]) {
          tempColour[i] += dimmConst;

          if (tempColour[i] >= targetColour[i]) {
            tempColour[i] = targetColour[i];
            matchFlag[i] = true;
          }
        } else {
          matchFlag[i] = true;
        }
      }
    }


    tempLedColour = CRGB(tempColour[0], tempColour[1], tempColour[2]);
    Serial.println("Set ind colour");
    fill_solid(leds, NUM_LEDS, tempLedColour); // Set the colour
    FastLED.show();
  }
  Serial.println("Out of while");

  return tempLedColour;
}


