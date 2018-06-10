// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//   Library Imports
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "FastLED.h"      // FastLED Library for NeoPixel Animation
#include <avr/power.h>    // Required Power library for Trinket


#define NUM_LEDS 50       // Define your strips
uint8_t leftEar[8] = {0,1,2,3,4,5,6,7};
uint8_t leftNub = 8;
uint8_t leftEye[16] = {14,15,16,17,18,19,20,21,22,23,24,9,10,11,12,13};
uint8_t rightEye[16] = {36,35,34,33,32,31,30,29,28,27,26,25,40,39,38,37};
uint8_t rightNub = 41;
uint8_t rightEar[8] = {49,48,47,46,45,44,43,42};




// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 0


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
