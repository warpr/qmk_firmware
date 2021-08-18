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
#define _MOD_L 3
#define _MOD_R 4
#define _SYSTEM 5

enum custom_keycodes {
  HOLD_MIN = (SAFE_RANGE | 0x0f) + 1,
  HOLD_MAX = HOLD_MIN + 0x10,
  DROP,
  WORD_L,  // emacs word left (ESC, B)
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

#define HOLD(layer) (HOLD_MIN | ((layer)&0x0F))
#define HOLD_SPC   LT(_MOD_L, KC_SPC)
#define HOLD_ENT   LT(_MOD_R, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_ESC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTRL, KC_A,   KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSPO, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,                               KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KW_FRSH, _______, KC_LOPT, KC_LCMD, HOLD(_MOD_L), HOLD_SPC,                    HOLD_SPC, HOLD_ENT, HOLD(_MOD_R), KW_NAV, KW_EMOJ, KW_DEVT
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

  [_MOD_L] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     DROP,    DROP,   TO(_NAV), TO(_SYM), DROP,   DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     DROP,    KC_LOPT, KC_LCMD, KC_LSFT, KC_LCTL, DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     DROP,    DROP,    DROP,    DROP,    _______, DROP,                               DROP,    DROP,    _______, DROP,    DROP,    DROP
  //└────────┴────────┴────────┴────────┴────────┴────────┘                          └────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_MOD_R] = LAYOUT_planck_grid(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    DROP,   TO(_SYM), TO(_NAV), DROP,   DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    KC_RCTL, KC_RSFT, KC_RCMD, KC_ROPT, DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     DROP,    DROP,    DROP,    DROP,    _______, DROP,                               DROP,    DROP,    _______, DROP,    DROP,    DROP
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

static uint8_t warp_hold_active = 0;

bool process_drop(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer = 0;

    switch (keycode) {
    case DROP:
        if (record->event.pressed) {
            for (int8_t i = MAX_LAYER - 1; i >= 0; i--) {
                if (layer_state_is(i)) {
                    if (DROP == keymap_key_to_keycode(i, record->event.key)) {
                        // turn off this layer, and continue dropping down.
                        layer_off(i);
                    } else {
                        // no DROP at this key pos in the current layer, we're done.
                        return true;
                    }
                }
            }

            // we've dropped all the way down to 0 and still found a DROP keycode there,
            // that doesn't seem a useful configuration.  Let's just claim we handled it.
            return false;
        }

        return false;

    case HOLD_SPC:
    case HOLD_ENT:
        if (record->tap.count) {
            // regular key press, leave this to QMK
            return true;
        }

        layer = (keycode >> 8) & 0x0F;
        uprintf("HOLD_SPC/HOLD_ENT is active. Switching to layer 0x%02X.  keycode is 0x%04X\n", layer, keycode);

        // fall through to HOLD key handling

    case HOLD_MIN ... HOLD_MAX:
        if (record->event.pressed) {
            if (!layer) {
                layer = keycode & 0x07;
            }
            layer_on(layer);
            uprintf("HOLD is active. Switching to layer 0x%02X.  keycode is 0x%04.  Mods are 0x%02X\n", layer, keycode, get_mods());
            warp_hold_active = 1;
            return false;
        } else {
            warp_hold_active = 0;
            layer_clear();
            uint8_t current_mods = get_mods();
            clear_mods();
            unregister_mods(current_mods);
            uprintf("HOLD released.  Mods are 0x%02X\n", get_mods());
            return false;
        }
        break;

    case KC_LCTRL ... KC_RGUI:
        if (record->event.pressed) {
            return true;
        } else {
            if (warp_hold_active) {
                uprintf("HOLD active, not releasing mods: 0x%02X\n", get_mods());
                // don't release mods while hold is active, just claim we handled it
                return false;
            } else {
                return true;
            }
        }
        break;
    }

    return true;
}

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

#define RGB(r, g, b)  {0x##r, 0x##g, 0x##b}

#define KW_WHITE    RGB(FF,FF,FF)   // white      -- spacing / navigation
#define KW_BLACK    RGB(00,00,00)   // black      -- key is off or transparent in this layer
#define KW_YELLO    RGB(FF,D0,00)   // yellow     -- punctuation + emoji macro
#define KW_LBLUE    RGB(63,82,F2)   // light blue -- alphas
#define KW_RED      RGB(FF,1C,3A)   // red        -- destructive keys
#define KW_GREEN    RGB(00,FF,77)   // green      -- modifiers
#define KW_PURPL    RGB(D0,00,FF)   // purple     -- macros
#define KW_BLUE     RGB(00,61,FF)   // blue       -- function keys

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_DVORAK] = {
        KW_WHITE, KW_YELLO, KW_YELLO, KW_YELLO, KW_LBLUE, KW_LBLUE,         KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_RED,
        KW_GREEN, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE,         KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_YELLO,
        KW_GREEN, KW_YELLO, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE,         KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_LBLUE, KW_GREEN,
        KW_PURPL, KW_BLACK, KW_GREEN, KW_GREEN, KW_YELLO,          KW_PURPL,          KW_PURPL, KW_GREEN, KW_GREEN, KW_YELLO, KW_PURPL
    },

    [_SYM] = {
        KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,         KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,
        KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,         KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO, KW_YELLO,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,         KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_GREEN, KW_GREEN, KW_GREEN, KW_BLACK,          KW_BLACK,          KW_BLACK, KW_GREEN, KW_GREEN, KW_BLACK, KW_BLACK
    },

    [_NAV] = {
        KW_BLACK, KW_RED,   KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_WHITE, KW_WHITE, KW_PURPL, KW_WHITE, KW_WHITE, KW_WHITE,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_WHITE, KW_PURPL, KW_PURPL, KW_PURPL, KW_WHITE, KW_WHITE,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_BLACK, KW_RED,   KW_RED,   KW_BLACK, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLACK, KW_GREEN, KW_GREEN, KW_BLACK,          KW_BLACK,           KW_BLACK, KW_GREEN, KW_GREEN,  KW_BLACK, KW_BLACK
    },

    [_MOD_L] = {
        KW_BLACK, KW_BLACK, KW_GREEN, KW_GREEN, KW_BLACK, KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_GREEN, KW_GREEN, KW_GREEN, KW_GREEN, KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,           KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK
    },

    [_MOD_R] = {
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_BLACK, KW_BLACK, KW_GREEN, KW_GREEN, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_BLACK, KW_GREEN, KW_GREEN, KW_GREEN, KW_GREEN, KW_BLACK,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,           KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK
    },

    [_SYSTEM] = {
        KW_BLACK, KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLACK,          KW_WHITE, KW_RED,   KW_RED,   KW_RED,   KW_BLACK, KW_BLACK,
        KW_BLACK, KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_WHITE,
        KW_BLACK, KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLUE,  KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_RED,
        KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK,           KW_BLACK,          KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK, KW_BLACK
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

/*
- tmk_core/common/action.c::process_record(record)
  |
  +-- quantum/quantum.c::process_record_quantum(record)
  |   |
  |   + -- process_record_kb(keycode, record)
  |   |    |
  |   |    +-- process_record_user(keycode, record)
  |   |
  |   +-- process_action_kb(record)
  |
  +-- process_record_handler(record)
  |   |
  |   +-- store_or_get_action(record->event.pressed, record->event.key)
  |   |   |
  |   |   +-- layer_switch_get_action(key)
  |   |
  |   +-- process_action(record, action)
  |
  +-- post_process_record_quantum(record)
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return (
        process_drop(keycode, record) &&
        process_emacs_nav(keycode, record)
    );
}
