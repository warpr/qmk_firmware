#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _LOWER 1

#define KUNO_REFRESH    SCMD(KC_R)
#define KUNO_DEVTOOLS   LCMD(A(KC_I))
#define KUNO_EMOJI      LCTL(LCMD(KC_SPC))

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  WORD_L,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPACE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,    KC_MPLY,       KUNO_EMOJI, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                 KC_LOPT, KC_LCMD, LT(_LOWER, KC_SPC),       LT(_LOWER, KC_ENT), KC_RCMD, KC_ROPT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      RESET,  DEBUG,   _______, _______, _______, KUNO_REFRESH,                 KUNO_DEVTOOLS, _______, _______, _______, DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_HOME,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TAB,                           _______, KC_SLASH, KC_EQL, KC_BSLS, KC_MINUS, KC_RCTL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, WORD_L,  KC_PGDN, KC_PGUP, WORD_R,  KC_END,  _______,          _______, _______, KC_LBRC, KC_PLUS, KC_RBRC, KC_GRAVE, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
  case WORD_L:
      // Emacs word left (ESC, B)
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_ESC)"b");
      }
      break;
  case WORD_R:
      // Emacs word right (ESC, F)
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_ESC)"f");
      }
      break;
  }
  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if (IS_LAYER_ON(_LOWER)) {
            if (clockwise) {
                backlight_increase();
            } else {
                backlight_decrease();
            }
        } else {
            if (clockwise) {
                tap_code16(KC_MS_WH_UP);
            } else {
                tap_code16(KC_MS_WH_DOWN);
            }
        }
    }

    return true;
}

void keyboard_post_init_keymap(void) {
#if BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(5);
#    ifdef BACKLIGHT_BREATHING
    breathing_enable();
#    endif
#endif
}
