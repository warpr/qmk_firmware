/**
 * Copyright 2015-2017 Jack Humbert
 * Copyright 2021      Kuno Woudt <kuno@frob.nl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "glow.h"
#include "muse.h"
#include "print.h"
#include "rgb_matrix.h"
#include "warpr.h"

#define LAYOUT_planck_grid_wrapper(...)      LAYOUT_planck_grid(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_planck_grid_wrapper(
      ____DVORAK_L1____, ____DVORAK_R1____,
      ____DVORAK_L2____, ____DVORAK_R2____,
      ____DVORAK_L3____, ____DVORAK_R3____,
      KW_FRSH, _______, ____DVORAK_L4____, KC_SPACE, KC_NO, ____DVORAK_R4____, KW_EMOJ,  KW_DEVT
    ),

    [_LOWER] = LAYOUT_planck_grid_wrapper(
      ____LOWER__L1____, ____LOWER__R1____,
      ____LOWER__L2____, ____LOWER__R2____,
      ____LOWER__L3____, ____LOWER__R3____,
      KW_FRSH, _______, ____LOWER__L4____, KC_SPACE, KC_NO, ____LOWER__R4____, KW_EMOJ,  KW_DEVT
    ),

    [_RAISE] = LAYOUT_planck_grid_wrapper(
      ____RAISE__L1____, ____RAISE__R1____,
      ____RAISE__L2____, ____RAISE__R2____,
      ____RAISE__L3____, ____RAISE__R3____,
      KW_FRSH, _______, ____RAISE__L4____, KC_SPACE, KC_NO, ____RAISE__R4____, KW_EMOJ,  KW_DEVT
    ),

    [_ADJUST] = LAYOUT_planck_grid_wrapper(
      ____ADJUST_L1____, ____ADJUST_R1____,
      ____ADJUST_L2____, ____ADJUST_R2____,
      ____ADJUST_L3____, ____ADJUST_R3____,
      KW_FRSH, _______, ____ADJUST_L4____, KC_SPACE, KC_NO, ____ADJUST_R4____, KW_EMOJ,  KW_DEVT
    ),

};

uint32_t update_planck_layer_leds(uint32_t state) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    switch (get_highest_layer(state)) {
        case _LOWER:
            planck_ez_left_led_on();
            break;
        case _RAISE:
            planck_ez_right_led_on();
            break;
        case _ADJUST:
            planck_ez_right_led_on();
            planck_ez_left_led_on();
            break;
        default:
            break;
    }

    return state;
}

uint32_t layer_state_set_user(uint32_t state) {
    return update_planck_layer_leds(
        update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST)
    );
}

void keyboard_pre_init_user(void) {
#ifdef AUDIO_ENABLE
    if (!is_audio_on()) {
        audio_on();
    }
#endif
}
void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

#define RGB(r, g, b)  {0x##r, 0x##g, 0x##b}

#define KW_WHITE    RGB(FF,FF,FF)   // white      -- spacing / navigation
#define KW_BLACK    RGB(00,00,00)   // black      -- key is off or transparent in this layer
#define KW_YELLO    RGB(FF,D0,00)   // yellow     -- punctuation + emoji macro
#define KW_LBLUE    RGB(63,82,F2)   // light blue -- alphas
#define KW_RED      RGB(FF,1C,3A)   // red        -- destructive keys
#define KW_GREEN    RGB(00,FF,77)   // green      -- modifiers
#define KW_PURPL    RGB(D0,00,FF)   // purple     -- macros
#define KW_BLUE     RGB(00,61,FF)   // blue       -- function keys

// FIXME: colors are outdated and don't match current keymap

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_DVORAK] = {
        KW_WHITE, KW_YELLO, KW_YELLO, KW_YELLO, KW_LBLUE, KW_LBLUE,         KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_RED,
        KW_GREEN, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE,         KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_YELLO,
        KW_GREEN, KW_YELLO, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE,         KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_GREEN,
        KW_PURPL, KW_BLACK, KW_GREEN, KW_GREEN, KW_YELLO,          KW_YELLO,          KW_PURPL, KW_GREEN, KW_GREEN, KW_YELLO, KW_PURPL
    },

    [_LOWER] = {
        KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,         KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,
        KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,         KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,
        KW_YELLO, KW_BLACK, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,         KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_BLACK, KW_YELLO,
        KW_PURPL, KW_BLACK, KW_GREEN, KW_GREEN, KW_YELLO,          KW_YELLO,          KW_PURPL, KW_GREEN, KW_GREEN, KW_YELLO, KW_PURPL
    },

    [_RAISE] = {
        KW_BLACK, KW_RED,   KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,         KW_WHITE, KW_WHITE, KW_PURPL, KW_WHITE, KW_WHITE, KW_WHITE,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,         KW_WHITE, KW_PURPL, KW_PURPL, KW_PURPL, KW_WHITE, KW_WHITE,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,         KW_BLACK, KW_PURPL, KW_RED,   KW_RED,   KW_BLACK, KW_BLACK,
        KW_PURPL, KW_BLACK, KW_GREEN, KW_GREEN, KW_YELLO,          KW_YELLO,          KW_PURPL, KW_GREEN, KW_GREEN, KW_YELLO, KW_PURPL
    },

    [_ADJUST] = {
        KW_BLACK, KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLACK,         KW_WHITE, KW_RED,   KW_RED,   KW_RED,   KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLACK,         KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_WHITE,
        KW_BLACK, KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLACK,         KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_RED,
        KW_PURPL, KW_BLACK, KW_GREEN, KW_GREEN, KW_YELLO,          KW_YELLO,          KW_PURPL, KW_GREEN, KW_GREEN, KW_YELLO, KW_PURPL
    },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    RGB rgb = {
      .r = pgm_read_byte(&ledmap[layer][i][0]),
      .g = pgm_read_byte(&ledmap[layer][i][1]),
      .b = pgm_read_byte(&ledmap[layer][i][2]),
    };

    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
  }
}

void rgb_matrix_indicators_user(void) {
  if (rgb_matrix_get_suspend_state() || keyboard_config.disable_layer_led) {
      return;
  }

  uint8_t layer = biton32(layer_state);
  switch (layer) {
  case 0 ... 5:
      set_layer_color(layer);
      break;
  default:
      if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
      }
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_warpr(keycode, record);
}
