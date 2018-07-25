// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time.

#include <FastLED.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define LIGHTPIN 4
#define SWITCHPIN 2
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS 50
#define BRIGHTNESS 55
CRGB leds[NUM_LEDS];

// colors to be reused
uint32_t colorArray[] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Lime, CRGB::Turquoise, CRGB::Blue, CRGB::BlueViolet, CRGB::Magenta};

//uint32_t nowColor = colorRed;
uint8_t  mode   = 8, // Current animation effect
         offset = 0, // Position of spinny eyes
         offsetEar = 0;  // Position of zippy ears

// element pin arrays
int leftEar[] = {0, 1, 2, 3, 4, 5, 6, 7};
int leftNub = 8;
int leftEye[] = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 9, 10, 11, 12, 13};
int rightEye[] = {36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 40, 39, 38, 37};
int rightNub = 41;
int rightEar[] = {49, 48, 47, 46, 45, 44, 43, 42};

// debouncing variables
#define switchGoStart 5
int switchGo = switchGoStart;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
    
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,LIGHTPIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // set the button on the right ear to use the pullup resistor
  pinMode(SWITCHPIN, INPUT_PULLUP);
}

void loop() {
  uint8_t  i;
  uint32_t t;

  switch (mode) {
    case 0:
      eightLoop(colorArray[0], 0);
      daftPulse();
      nubBlink(colorArray[0]);
      t = 75;
      break;
    case 1:
      eightLoop(colorArray[1], 1);
      daftPulse();
      nubBlink(colorArray[1]);
      t = 55;
      break;
    case 2:
      eightLoop(colorArray[2], 0);
      daftPulse();
      nubBlink(colorArray[2]);
      t = 50;
      break;
    case 3:
      eightLoop(colorArray[3], 1);
      daftPulse();
      nubBlink(colorArray[3]);
      t = 75;
      break;
    case 4:
      eightLoop(colorArray[4], 0);
      daftPulse();
      nubBlink(colorArray[4]);
      t = 128;
      break;
    case 5:
      eightLoop(colorArray[5], 1);
      daftPulse();
      nubBlink(colorArray[5]);
      t = 66;
      break;
    case 6:
      eightLoop(colorArray[6], 0);
      daftPulse();
      nubBlink(colorArray[6]);
      t = 111;
      break;
    case 7:
      eightLoop(colorArray[7], 1);
      daftPulse();
      nubBlink(colorArray[7]);
      t = 128;
      break;
    case 8:
      eightLoop(CRGB::White, 0);
      daftPulse();
      nubBlink(CRGB::White);
      t = 75;
      break;
  }

  FastLED.show();
  delay(t);

  if (switchGo != 0) {
    switchGo--;
  }

  // TODO: Debounce switch button
  if (! digitalRead(SWITCHPIN)) {    // Every 8 seconds...
    if (switchGo <= 0) {
      mode++;                        // Next mode
      if (mode > 8) {                // End of modes?
        mode = 0;                    // Start modes over
      }
      for (i = 0; i < 50; i++){
        leds[i] = CRGB::Black;
      }
      switchGo = switchGoStart;
    }
  }
}

void daftPulse() {
  uint8_t j;
  int bounceValue = bounceNum(offsetEar, 8);

  for (j = 0; j < 8; j++) {
    if (bounceValue > j) {
      leds[leftEar[j]] = colorArray[j];  //left ear
      leds[rightEar[j]] = colorArray[j]; // right ear
    } else {
      leds[leftEar[j]] = CRGB::Black;  //left ear
      leds[rightEar[j]] = CRGB::Black; // right ear
    }
  }

  offsetEar++;
  if (offsetEar == 16) offset = 0;
}

int bounceNum(int n, int max)
{
  return abs(((n % (max * 2)) - max) * (1 - (((n / (max * 2)) % 2) * 2)));
}

void nubBlink(uint32_t sentColor) {
  if (offset > 8) {
    leds[leftNub] = sentColor;
    leds[rightNub] = sentColor;
  } else {
    leds[leftNub] = CRGB::Black;
    leds[rightNub] = CRGB::Black;
  }
}

void eightLoop(uint32_t sentColor, uint8_t sentMode) {
  uint8_t  i;
  // Spin the lenses
  for (i = 0; i < 16; i++) {
    switch (sentMode) {
      case 0:
        if (i == (offset % 16) || i == ((offset % 16) + 1)) {
          leds[leftEye[i]] = sentColor; // both eyes in a figure 8
          leds[rightEye[i]] = sentColor; // both eyes in a figure 8
        } else {
          leds[leftEye[i]].fadeToBlackBy(200); // both eyes in a figure 8
          leds[rightEye[i]].fadeToBlackBy(200); // both eyes in a figure 8
        }
        break;
      case 1:
        leds[leftEye[i]].fadeToBlackBy(200); // both eyes in a figure 8
        leds[rightEye[i]].fadeToBlackBy(200); // both eyes in a figure 8
        uint8_t ledA = random8(9,25);
        uint8_t ledB = random8(25,41);
        leds[ledA] = sentColor; // both eyes in a figure 8
        leds[ledB] = sentColor; // both eyes in a figure 8
        break;
    }
  }
  offset++;
  if (offset == 16) offset = 0;
}

