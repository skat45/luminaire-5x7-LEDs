void settings() {
  switch (this_mode) {
    case 2:
      switch (setting_num) {
        case 1:
          if (bLeft.isHolded()) {
            drug_mode = false;
            EEPROM.put(2, drug_mode);
          }
          if (bRight.isHolded()) {
            drug_mode = true;
            EEPROM.put(2, drug_mode);
          }

          FastLED.clear();
          rainbow_hue++;
          if (drug_mode) {
            for (byte i; i < NUM_LEDS; i++) {
              leds[i] = CHSV(rainbow_hue, 255, 255);
            }
            draw_white(2, 7);
            draw_white(4, 7);
            clean_pixel(1, 2);
            clean_pixel(2, 2);
            clean_pixel(3, 2);
            clean_pixel(3, 1);
          }
          else {
            draw_hsv(3, 3, rainbow_hue);
            draw_hsv(4, 3, rainbow_hue);
            draw_hsv(4, 4, rainbow_hue);
            draw_hsv(5, 4, rainbow_hue);
            draw_hsv(4, 5, rainbow_hue);
          }
          draw_hsv(2, 1, 130);
          draw_hsv(1, 1, 12);
          break;

        case 2:
          uint32_t t = millis();
          if (bLeft.isHolded()) {
            reverse_mode = true;
            EEPROM.put(3, reverse_mode);
          }
          if (bRight.isHolded()) {
            reverse_mode = false;
            EEPROM.put(3, reverse_mode);
          }
          FastLED.clear();
          rainbow_hue++;
          draw_hsv(reverse_sett_num, 3, rainbow_hue);
          draw_hsv(reverse_sett_num, 4, rainbow_hue);
          draw_hsv(reverse_sett_num, 5, rainbow_hue);
          draw_hsv(2, 1, 60);
          draw_hsv(1, 1, 60);
          if (t - lastUpdateTime > reverse_update_interval) {
            lastUpdateTime = t;
            if (reverse_mode) {
              reverse_sett_num--;
              if (reverse_sett_num == 0) reverse_sett_num = 5;
            }
            else {
              reverse_sett_num++;
              if (reverse_sett_num == 6) reverse_sett_num = 1;
            }
          }
          break;
      }

      if (setting_num == 3) {
        FastLED.clear();
        draw_hsv(2, 1, 85);
        draw_hsv(1, 1, 85);
        for (byte i = 1; i <= 5; i++) draw_dark_white(i, 4);
        for (byte j = 3; j <= 6; j++) draw_hsv(rainbow_speed_mode, j, rainbow_hue);
        uint32_t t = millis();
        if (t - lastUpdateTime > updateRainbowInterval) {
          lastUpdateTime = t;
          if (!reverse_mode) rainbow_hue++;
          else rainbow_hue--;
        }
        if (bLeft.isHolded()) {
          rainbow_speed_mode--;
          if (rainbow_speed_mode == 0) rainbow_speed_mode = 1;
          updateRainbowInterval = rainbow_speed[rainbow_speed_mode - 1];
          EEPROM.put(4, rainbow_speed_mode);
        }
        if (bRight.isHolded()) {
          rainbow_speed_mode++;
          if (rainbow_speed_mode == 6) rainbow_speed_mode = 5;
          updateRainbowInterval = rainbow_speed[rainbow_speed_mode - 1];
          EEPROM.put(4, rainbow_speed_mode);
        }
      }
      break;

    case 3:
      switch (setting_num) {
        case 1:
          FastLED.clear();
          if (bLeft.isHolded()) {
            ladder_hue -= 15;
            EEPROM.put(6, ladder_hue);
          }
          if (bRight.isHolded()) {
            ladder_hue += 15;
            EEPROM.put(6, ladder_hue);
          }
          uint32_t t = millis();
          if (t - lastUpdateTime > ladder_update_interval) {
            lastUpdateTime = t;
            ladder_num++;
            if (ladder_num == 10) ladder_num = 0;
          }
          draw_hsv(1, 1, ladder_hue - 15);
          draw_hsv(2, 1, ladder_hue + 15);
          for (byte x = 1; x <= 5; x++) {
            for (byte y = 4; y <= 5; y++) {
              leds[(x - 1) * 7 + y - 1] = CHSV(ladder_hue, 255, 100 + ladder_values[ladder_num] * 31);
            }
          }
          break;
      }
      if (setting_num == 2) {
        FastLED.clear();
        uint32_t t = millis();
        if (t - lastUpdateTime > ladder_update_interval) {
          lastUpdateTime = t;
          ladder_num++;
          if (ladder_num == 10) ladder_num = 0;
        }
        if (bLeft.isHolded()) {
          ladder_update_interval_num--;
          if (ladder_update_interval_num == 0) ladder_update_interval_num = 1;
          ladder_update_interval = ladder_update_intervals[ladder_update_interval_num - 1];
          EEPROM.put(5, ladder_update_interval_num);
        }
        if (bRight.isHolded()) {
          ladder_update_interval_num++;
          if (ladder_update_interval_num == 6) ladder_update_interval_num = 5;
          ladder_update_interval = ladder_update_intervals[ladder_update_interval_num - 1];
          EEPROM.put(5, ladder_update_interval_num);
        }
        rainbow_hue++;
        draw_hsv(2, 1, rainbow_hue);
        draw_hsv(1, 1, rainbow_hue);
        for (byte i = 1; i <= 5; i++) draw_dark_white(i, 4);
        for (byte j = 3; j <= 6; j++) leds[(ladder_update_interval_num - 1) * 7 + j - 1] = CHSV(ladder_hue, 255, ladder_values[ladder_num] * 51);
      }
      break;

    case 4:
      FastLED.clear();
      if (bLeft.isHolded()) {
        color_hue -= 15;
        EEPROM.put(7, color_hue);
      }
      if (bRight.isHolded()) {
        color_hue += 15;
        EEPROM.put(7, color_hue);
      }
      draw_hsv(1, 1, color_hue - 15);
      draw_hsv(2, 1, color_hue + 15);
      for (byte x = 1; x <= 5; x++) {
        for (byte y = 4; y <= 5; y++) {
          draw_hsv(x, y, color_hue);
        }
      }
      break;

    case 5:
      for (byte i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(0, 0, 255);
      }
      FastLED.show();
      break;
  }

  draw_white(1, 7);
  draw_white(3, 7);
  draw_white(5, 7);
  FastLED.show();
}
