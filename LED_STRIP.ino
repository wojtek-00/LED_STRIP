#include <FastLED.h>

#define LED_PIN     2     // Pin do którego podłączona jest taśma LED
#define NUM_LEDS    50    // Liczba diod LED w taśmie
#define BRIGHTNESS  255    // Maksymalna jasność LED
int relyPin = 4;

CRGB leds[NUM_LEDS];

CRGB colour = CRGB::White; // Poprawna deklaracja koloru

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS); // Inicjalizacja taśmy
  FastLED.setBrightness(BRIGHTNESS); // Ustawienie jasności
  pinMode(relyPin, OUTPUT);
  digitalWrite(relyPin, LOW);
  delay(100);
}

void loop() {
  //breathingEffect(15, colour); // Wywołanie funkcji efektu oddychania
  rainbowWave(20); // Wywołanie efektu tęczowego
  //twinkleEffect(30, colour);    // Efekt skręcania
  //colorBurstEffect(1000); // Efekt wybuchu kolorów
  //waveEffect(100, colour);       // Efekt fali
  //plainColour(colour);
}

void plainColour(CRGB colour_fun) {
  fill_solid(leds, NUM_LEDS, colour_fun); // Ustaw kolor na zadany
  FastLED.show(); // Wyświetlenie ustawionych kolorów
}

// Efekt oddychania
void breathingEffect(uint8_t wait, CRGB colour_fun) {
  // Przejrzystość od minimalnej do maksymalnej
  for (int brightness = 25; brightness <= 255; brightness++) {
    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, colour_fun); // Ustaw kolor na biały
    FastLED.show();
    delay(wait);
  }
  // Przejrzystość od maksymalnej do minimalnej
  for (int brightness = 255; brightness >= 25; brightness--) {
    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, colour_fun); // Ustaw kolor na biały
    FastLED.show();
    delay(wait);
  }
}

// Efekt tęczowy
void rainbowWave(uint8_t wait) {
  static uint16_t j = 0; // Zmienna do cyklu
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = Wheel((i + j) & 255); // Ustawienie koloru na podstawie funkcji Wheel
  }
  FastLED.show(); // Wyświetlenie ustawionych kolorów
  j += 1; // Zwiększanie zmiennej cyklu
  delay(wait); // Opóźnienie
}

void twinkleEffect(uint8_t wait, CRGB colour_fun) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colour_fun; // Ustawienie koloru na biały
    FastLED.show();
    delay(wait);
    leds[i] = CRGB::Black; // Wyłączenie diody
  }
}

void colorBurstEffect(uint8_t wait) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(random(256), random(256), random(256)); // Losowy kolor
  }
  FastLED.show();
  delay(wait);
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Wyłączenie diod
  FastLED.show();
}

void waveEffect(uint8_t wait, CRGB colour_fun) {
  static uint8_t waveIndex = 0; // Zmienna do przesunięcia fali
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; // Wyłączenie diod
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 6 == waveIndex) {
      leds[i] = colour_fun;
    }
  }
  
  FastLED.show();
  waveIndex = (waveIndex + 1) % 3; // Przesunięcie indeksu fali
  delay(wait);
}


// Funkcja do generowania kolorów
CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos; // Odwracanie kolorów
  if (WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3); // Przejście od czerwonego do zielonego
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3); // Przejście od zielonego do niebieskiego
  } else {
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0); // Przejście od niebieskiego do czerwonego
  }
}
