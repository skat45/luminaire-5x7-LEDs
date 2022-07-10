uint32_t lastUpdateTime = 0;

// #1 FIRE
void fire_led() {
  uint32_t t = millis();
  if (t - lastUpdateTime > updateFireInterval) {
    updateFireInterval = random(10, 100);
    lastUpdateTime = t;
    for (byte i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(fire_hue[i], 255, random(200, 255));
      fire_hue[i] = fire_hue[i] + random(-5, 5);
      if (fire_hue[i] < startFireHue) fire_hue[i] = startFireHue;
      if (fire_hue[i] > endFireHue) fire_hue[i] = endFireHue;
    }
    FastLED.show();
  }
}


// #2 RAINBOW
void rainbow_led() {
  uint32_t t = millis();
  if (t - lastUpdateTime > updateRainbowInterval) {
    lastUpdateTime = t;
    if (!reverse_mode) rainbow_hue++;
    else rainbow_hue--;
  }
  if (drug_mode) {
    if (!reverse_mode) rainbow_hue++;
    else rainbow_hue--;
  }

  for (byte i; i < NUM_LEDS; i++) {
    leds[i] = CHSV(rainbow_hue, 255, 255);
  }
  FastLED.show();
}


// #3 LADDER
void ladder_led() {
  uint32_t t = millis();
  if (t - lastUpdateTime > ladder_update_interval) {
    lastUpdateTime = t;
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(ladder_hue, 255, 100 + ladder_values[ladder_num] * 31);
    ladder_num++;
    if (ladder_num == 10) ladder_num = 0;
  }
  FastLED.show();
}


// #4 COLOR
void color_led() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(color_hue, 255, 255);
  }
  FastLED.show();
}


// #5 JUST LIGHT/WARM LIGHT
void light_led() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(30, (255/100)*58, 255);
  }
  FastLED.show();
}



// DRAWING BY XY HUI
void draw_hsv(byte x, byte y, byte hue) {
  leds[(x - 1) * 7 + y - 1] = CHSV(hue, 255, 255);
}

void draw_white(byte x, byte y) {
  leds[(x - 1) * 7 + y - 1] = CHSV(0, 0, 255);
}

void draw_dark_white(byte x, byte y) {
  leds[(x - 1) * 7 + y - 1] = CHSV(0, 0, 102);
}

void clean_pixel(byte x, byte y) {
  leds[(x - 1) * 7 + y - 1] = CHSV(0, 0, 0);
}
