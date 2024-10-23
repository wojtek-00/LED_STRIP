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


void breathingEffect(int wait, CRGB colour_fun) {
  for (int brightness = 255; brightness >= 45; brightness--) {
    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, colour_fun);
    FastLED.show();
    delay(wait);
  }

  for (int brightness = 45; brightness <= 255; brightness++) {
    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, colour_fun);
    FastLED.show();
    delay(wait);
  }
}


void rainbowWave(int wait) {
  static uint16_t j = 0;
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = Wheel((i + j) & 255);
  }
  FastLED.show();
  j += 1;
  delay(wait);
}

void twinkleEffect(int wait, CRGB colour_fun) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colour_fun;
    FastLED.show();
    delay(wait);
    leds[i] = CRGB::Black;
  }
}

void colorBurstEffect(int wait) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(random(256), random(256), random(256));
  }
  FastLED.show();
  delay(wait);
}

void waveEffect(int wait, CRGB colour_fun) {
  static uint8_t waveIndex = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 6 == waveIndex) {
      leds[i] = colour_fun;
    }
  }
  
  FastLED.show();
  waveIndex = (waveIndex + 1) % 3;
  delay(wait);
}


// Generate the colours
CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3); // move from red to green
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3); // move from green to blue
  } else {
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0); // move from blue to red
  }
}
