#include <EEPROM.h>

// LED STRIPE
#include <FastLED.h>
#define NUM_LEDS 35
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

// BUTTONS
#include <bb.h>
#define MIDDLEBTNPIN 2
bb bLeft(4, 10);
bb bMiddle(MIDDLEBTNPIN, 10);
bb bRight(3, 10);

// DIFFERENT
#define EEPROM0 1
byte this_mode = EEPROM0; // 0
bool is_on = true;
bool setting_mode = false;
byte setting_num = 1;
const byte setting_max_num[] = {1, 3, 2, 1, 1};
#define MAXMODE 5
#define EEPROM1 255
byte brightness = EEPROM1; // 1

// Fire
byte fire_hue[NUM_LEDS];
byte updateFireInterval;
#define startFireHue 6
#define endFireHue 20

// Rainbow
byte updateRainbowInterval = 100;
#define EEPROM2 false
bool drug_mode = EEPROM2; // 2
#define EEPROM3 false
bool reverse_mode = EEPROM3; // 3
#define EEPROM4 3
byte rainbow_speed_mode = EEPROM4; // 4
byte rainbow_hue = 0;
#define reverse_update_interval 200
byte reverse_sett_num = 3;
const byte rainbow_speed[] = {1000, 200, 100, 50, 10};

// Ladder
#define EEPROM5 4
byte ladder_update_interval_num = EEPROM5; // 5
#define EEPROM6 70
byte ladder_hue = EEPROM6; // 6
const byte ladder_values[] = {1, 3, 2, 4, 3, 5, 3, 4, 2, 3}; // 10 elements
byte ladder_num = 0;
const uint16_t ladder_update_intervals[] = {5000, 2000, 250, 150, 100};
uint16_t ladder_update_interval = 200;

// Color
#define EEPROM7 140
byte color_hue = EEPROM7; // 7

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  pinMode(8, INPUT);
  randomSeed(analogRead(8));
  for (byte i = 0; i < NUM_LEDS; i++) fire_hue[i] = random(startFireHue, endFireHue);
  updateFireInterval = random(10, 255);

  // Reading from EEPROM
  this_mode = EEPROM[0];
  brightness = EEPROM[1];
  drug_mode = EEPROM[2];
  reverse_mode = EEPROM[3];
  rainbow_speed_mode = EEPROM[4];
  updateRainbowInterval = rainbow_speed[rainbow_speed_mode - 1];
  ladder_update_interval_num = EEPROM[5];
  ladder_update_interval = ladder_update_intervals[ladder_update_interval_num - 1];
  ladder_hue = EEPROM[6];
  color_hue = EEPROM[7];
}

void loop() {
  bLeft.check();
  bMiddle.check();
  bRight.check();
  btn_checker();
  FastLED.setBrightness(brightness);
  if (is_on) {
    if (setting_mode) settings();
    else {
      switch (this_mode) {
        case 1:
          fire_led();
          break;

        case 2:
          rainbow_led();
          break;

        case 3:
          ladder_led();
          break;

        case 4:
          color_led();
          break;

        case 5:
          light_led();
          break;
      }
    }
  }
  else {
    FastLED.clear();
    FastLED.show();
  }
}
