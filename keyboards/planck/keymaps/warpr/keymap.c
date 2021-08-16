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

#define _DVORAK 0
#define _SYM 1
#define _NAV 2
#define _SYSTEM 3

enum custom_keycodes {
  WORD_L = SAFE_RANGE,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
  PAGE_B,  // emacs backward-page, C-X [
  PAGE_F,  // emacs forward-page, C-X ]
};

#define KW_FRSH    SCMD(KC_R)    // browser refresh
#define KW_DEVT    LCMD(A(KC_I))  // browser dev tools
#define KW_EMOJ    LCTL(LCMD(KC_SPC))

#define KW_SPACE   LT(_SYM, KC_SPC)
#define KW_ENTER   LT(_SYM, KC_ENT)
#define KW_NAV     MO(_NAV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_ESC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTRL, KC_A,   KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSPO, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,                               KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KW_FRSH, _______, KC_LOPT, KC_LCMD, KW_SPACE, KW_SPACE,                         KW_SPACE, KW_ENTER, KW_NAV, KW_NAV,  _______, KW_DEVT
  //└────────┴────────┴────────┴────────┴────────┴────────┘                          └────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_SYM] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPACE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  S(KC_LBRC), KC_LBRC, S(KC_4), KC_RBRC, S(KC_RBRC),                     S(KC_SLASH), KC_SLASH, KC_EQL, KC_BSLS, S(KC_BSLS), KC_KP_PLUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  S(KC_1), S(KC_2), S(KC_3), S(KC_GRAVE), S(KC_5),                       S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______
  //└────────┴────────┴────────┴────────┴────────┴────────┘                          └────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, RESET,   _______, _______, _______, _______,                            PAGE_B,  WORD_L,  KC_UP,   WORD_R,  KC_PGUP, KC_HOME,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            PAGE_F,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_END,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______
  //└────────┴────────┴────────┴────────┴────────┴────────┘                          └────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_SYSTEM] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                            KC_INS,  KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,                            _______, _______, _______, _______, _______, RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______
  //└────────┴────────┴────────┴────────┴────────┴────────┘                          └────────┴────────┴────────┴────────┴────────┴────────┘
  )

};

bool process_emacs_nav(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case WORD_L:
        // Emacs word left (ESC, B)
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC) "b");
        }
        return false;

    case WORD_R:
        // Emacs word right (ESC, F)
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC) "f");
        }
        return false;

    case PAGE_B:
        // Emacs backward-page, C-X [
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("x"));
        } else {
            SEND_STRING("[");
        }
        return false;

    case PAGE_F:
        // Emacs forward-page, C-X ]
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("x"));
        } else {
            SEND_STRING("]");
        }
        return false;
    }

    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _SYSTEM);
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

// Oryx colors
// alphas       = Solarized -> Lavendar
// modifiers    = Rubik's Cube -> Green
// destructive  = Rubik's Cube -> Red
// punctuation  = Rubik's Cube -> Orange
// spacing      = Cosmic Chocolate -> White
// navigation   = Cosmic Chocolate -> White
// emoji        = Rubik's Cube -> Yellow
// macros       = Sunset -> Purple

#define KWC_WHITE        {0,0,255}
#define KWC_BLACK        {0,0,0}
#define KWC_YELLO        {35,255,255}
#define KWC_BLUE         {161,151,242}
#define KWC_RED          {249,228,255}
#define KWC_GREEN        {105,255,255}
#define KWC_PURPL        {205,255,255}
#define KWC_BLUE2        {154,255,255}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_DVORAK] = {
        KWC_WHITE, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_BLUE,  KWC_BLUE,           KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_RED,
        KWC_GREEN, KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,           KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_YELLO,
        KWC_GREEN, KWC_YELLO, KWC_BLUE , KWC_BLUE,  KWC_BLUE,  KWC_BLUE,           KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_BLUE,  KWC_GREEN,
        KWC_PURPL, KWC_BLACK, KWC_GREEN, KWC_GREEN, KWC_YELLO,           KWC_PURPL,           KWC_PURPL, KWC_GREEN, KWC_GREEN, KWC_YELLO, KWC_PURPL
    },

    [_SYM] = {
        KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO,          KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO,
        KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO,          KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO, KWC_YELLO,
        KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK,          KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK,
        KWC_BLACK, KWC_GREEN, KWC_GREEN, KWC_GREEN, KWC_BLACK,           KWC_BLACK,           KWC_BLACK, KWC_GREEN, KWC_GREEN, KWC_BLACK, KWC_BLACK
    },

    [_NAV] = {
        KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK,          KWC_WHITE, KWC_WHITE, KWC_PURPL, KWC_WHITE, KWC_WHITE, KWC_WHITE,
        KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK,          KWC_WHITE, KWC_PURPL, KWC_PURPL, KWC_PURPL, KWC_WHITE, KWC_WHITE,
        KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK,          KWC_BLACK, KWC_RED,   KWC_RED,   KWC_BLACK, KWC_BLACK, KWC_BLACK,
        KWC_BLACK, KWC_BLACK, KWC_GREEN, KWC_GREEN, KWC_BLACK,           KWC_BLACK,           KWC_BLACK, KWC_GREEN, KWC_GREEN, KWC_BLACK, KWC_BLACK
    },

    [_SYSTEM] = {
        KWC_BLACK, KWC_BLUE2, KWC_BLUE2, KWC_BLUE2, KWC_BLUE2, KWC_BLACK,          KWC_WHITE, KWC_RED,   KWC_RED,   KWC_RED,   KWC_BLACK, KWC_BLACK,
        KWC_BLACK, KWC_BLUE2, KWC_BLUE2, KWC_BLUE2, KWC_BLUE2, KWC_BLACK,          KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_WHITE,
        KWC_BLACK, KWC_BLUE2, KWC_BLUE2, KWC_BLUE2, KWC_BLUE2, KWC_BLACK,          KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_RED,
        KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK,           KWC_BLACK,           KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK, KWC_BLACK
    },
};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (rgb_matrix_get_suspend_state() || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_emacs_nav(keycode, record);
}
