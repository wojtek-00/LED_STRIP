#include "functions_led.h"
#include "parameters.h"
#include <Arduino.h>

void ledOff(){
  FastLED.setBrightness(0);
  FastLED.show();
}

void plainColour(CRGB colour_fun) {
  FastLED.setBrightness(255);
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
      brightness++;
      if (brightness >= 255) {
        increasing = false;  // When we reach maximum brightness, change direction
      }
    } else {
      brightness--;
      if (brightness <= 25) {
        increasing = true;   // When we reach minimum brightness, change direction
      }
    }

    // Set the brightness and display the colour
    FastLED.setBrightness(brightness);
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
      leds[i] = CRGB(random(256), random(256), random(256));
    }
    FastLED.show();
  }
}

void waveEffect(int interval, CRGB colour_fun) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    static uint8_t waveIndex = 0;

    // Clear all LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }

    // Set the appropriate LEDs to the colour
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 6 == waveIndex) { // You can change 6 to another value for different effects
        leds[i] = colour_fun;
      }
    }

    FastLED.show();
    
    // Increase the wave index and reset to zero when reaching NUM_LEDS
    waveIndex = (waveIndex + 1) % 6; // Changed to 6 to match the condition
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
