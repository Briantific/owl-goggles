// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define LIGHTPIN 4
#define SWITCHPIN 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(50, LIGHTPIN);

// colors to be reused
uint32_t colorRed = 0xFF0000;     //red
uint32_t colorOrange = 0xFF8800;
uint32_t colorYellow = 0xFFFF00;
uint32_t colorGreen = 0x00FF00;
uint32_t colorTeal = 0x00FFFF;
uint32_t colorBlue = 0x0000FF;
uint32_t colorIndigo = 0x8800FF;
uint32_t colorViolet = 0xFF00FF;
uint32_t colorWhite = 0xFFFFFF;

uint32_t colorArray[] = {colorRed, colorOrange, colorYellow, colorGreen, colorTeal, colorBlue, colorIndigo, colorViolet};

uint32_t nowColor = colorRed;
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
int figureEight[] = {leftEye[15], leftEye[14], leftEye[13], leftEye[12], leftEye[11], leftEye[10], leftEye[9], leftEye[8], rightEye[7], rightEye[6], rightEye[5], rightEye[4], rightEye[3], rightEye[2], rightEye[1], rightEye[0], rightEye[15], rightEye[14], rightEye[13], rightEye[12], rightEye[11], rightEye[10], rightEye[9], rightEye[8], leftEye[7], leftEye[6], leftEye[5], leftEye[4], leftEye[3], leftEye[2], leftEye[1], leftEye[0]};

// debouncing variables
#define switchGoStart 5
int switchGo = switchGoStart;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(55); // 1/3 brightness
  pinMode(SWITCHPIN, INPUT_PULLUP);
}

void loop() {
  uint8_t  i;
  uint32_t t;

  switch (mode) {
    case 0:
      eightLoop(colorArray[0]);
      daftPulse();
      nubBlink(colorArray[0]);
      break;
    case 1:
      eightSparkle(colorArray[1]);
      samePulse(colorArray[1]);
      nubBlink(colorArray[1]);
      break;
    case 2:
      eightLoop(colorArray[2]);
      daftPulse();
      nubBlink(colorArray[2]);
      break;
    case 3:
      eightSparkle(colorArray[3]);
      samePulse(colorArray[3]);
      nubBlink(colorArray[3]);
      break;
    case 4:
      eightLoop(colorArray[4]);
      daftPulse();
      nubBlink(colorArray[4]);
      break;
    case 5:
      eightSparkle(colorArray[5]);
      samePulse(colorArray[5]);
      nubBlink(colorArray[5]);
      break;
    case 6:
      eightLoop(colorArray[6]);
      daftPulse();
      nubBlink(colorArray[6]);
      break;
    case 7:
      eightSparkle(colorArray[7]);
      samePulse(colorArray[7]);
      nubBlink(colorArray[7]);
      break;
    case 8:
      eightLoop(colorWhite);
      daftPulse();
      nubBlink(colorWhite);
      break;
  }

  pixels.show();
  delay(80);

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
      for (i = 0; i < 50; i++) pixels.setPixelColor(i, 0);
      switchGo = switchGoStart;
    }
  }
}

void daftPulse() {
  uint8_t j;
  int bounceValue = bounceNum(offsetEar, 8);

  for (j = 0; j < 8; j++) {
    if (bounceValue > j) {
      pixels.setPixelColor(leftEar[j], colorArray[j]);  //left ear
      pixels.setPixelColor(rightEar[j], colorArray[j]); // right ear
    } else {
      pixels.setPixelColor(leftEar[j], 0);  //left ear
      pixels.setPixelColor(rightEar[j], 0); // right ear
    }
  }

  offsetEar++;
  if (offsetEar == 16) offset = 0;
}

void samePulse(uint32_t sentColor) {
  uint8_t j;
  int bounceValue = bounceNum(offsetEar, 8);

  for (j = 0; j < 8; j++) {
    if (bounceValue > j) {
      pixels.setPixelColor(leftEar[j], sentColor);  //left ear
      pixels.setPixelColor(rightEar[j], sentColor); // right ear
    } else {
      pixels.setPixelColor(leftEar[j], 0);  //left ear
      pixels.setPixelColor(rightEar[j], 0); // right ear
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
  if (offset > 15) {
    pixels.setPixelColor( leftNub, sentColor);
    pixels.setPixelColor( rightNub, sentColor);
  } else {
    pixels.setPixelColor( leftNub, 0);
    pixels.setPixelColor( rightNub, 0);
  }

  offset++;
  if (offset == 30) offset = 0;
}

void eightLoop(uint32_t sentColor) {
  uint8_t  i;
  // Spin the lenses
  for (i = 0; i < 32; i++) {
    uint32_t c = 0;
    if (i == (offset % 31) || i == ((offset % 31) + 1)) {
      c = sentColor; // 4 pixels on...
    }
    pixels.setPixelColor(figureEight[i], c); // both eyes in a figure 8
  }
  offset++;
  if (offset == 32) offset = 0;
}

void eightSparkle(uint32_t sentColor) {
  uint8_t  i;
  // Spin the lenses
  for (i = 0; i < 32; i++) {
    uint32_t c = 0;
    uint8_t randNumber = random(0, 31);
    if (i == (offset % 31) || i == ((offset % 31) + 1)) {
      c = sentColor; // 4 pixels on...
    }
    pixels.setPixelColor(figureEight[randNumber], c); // both eyes in a figure 8
  }
  offset++;
  if (offset == 32) offset = 0;
}

