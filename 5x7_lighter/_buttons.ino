uint32_t last_pm_hold = 0;
#define setBrightnessInterval 350

void btn_checker() {
  uint32_t t = millis();

  // LIGHTS ON/OFF
  if (bMiddle.isSingle()) is_on = !is_on;


  // SWITCH LED MODES
  if (is_on && !setting_mode) {
    if (bLeft.isSingle()) {
      this_mode--;
      if (this_mode == 0) this_mode = MAXMODE;
      EEPROM.put(0, this_mode);
    }
    if (bRight.isSingle()) {
      this_mode++;
      if (this_mode > MAXMODE) this_mode = 1;
      EEPROM.put(0, this_mode);
    }
  }


  // SETTINGS  MODE ON/OFF
  if (is_on && bMiddle.isHolded()) {
    setting_mode = !setting_mode;
    setting_num = 1;
  }


  // SWITCH SETTING MODES
  if (is_on && setting_mode) {
    if (bLeft.isSingle()) {
      setting_num--;
      if (setting_num == 0) setting_num = setting_max_num[this_mode - 1];
    }
    if (bRight.isSingle()) {
      setting_num++;
      if (setting_num > setting_max_num[this_mode - 1]) setting_num = 1;
    }
  }

  // SETTING BRIGHTNESS
  if (is_on && !setting_mode) {
    if (bLeft.isHold() && t - last_pm_hold > setBrightnessInterval) {
      last_pm_hold = t;
      if (brightness > 40) brightness -= 20;
      EEPROM.put(1, brightness);
    }
    if (bRight.isHold() && t - last_pm_hold > setBrightnessInterval) {
      last_pm_hold = t;
      if (brightness < 255) brightness += 20;
      EEPROM.put(1, brightness);
    }
  }


  // RESET SETTINS
  if (is_on && bMiddle.isTriple()) {
    // Default settings to EEPROM
    EEPROM.put(0, EEPROM0);
    EEPROM.put(1, EEPROM1);
    EEPROM.put(2, EEPROM2);
    EEPROM.put(3, EEPROM3);
    EEPROM.put(4, EEPROM4);
    EEPROM.put(5, EEPROM5);
    EEPROM.put(6, EEPROM6);
    EEPROM.put(7, EEPROM7);
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
    rainbow_hue = 0;
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(0, 255, 255);
    FastLED.show();
    delay(250);
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(85, 255, 255);
    FastLED.show();
    delay(250);
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(170, 255, 255);
    FastLED.show();
    delay(250);
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(255, 255, 255);
    FastLED.show();
    delay(250);
  }
}
