#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2
#define CMD_TIMEOUT 750

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE,
  WORD_L,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
};

static bool cmd_held = false;
static uint16_t cmd_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPACE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL_T(KC_TAB), LCTL_T(KC_A), LSFT_T(KC_O), LALT_T(KC_E), LCMD_T(KC_U), KC_I,                  KC_D, RCMD_T(KC_H), RALT_T(KC_T), RSFT_T(KC_N), RCTL_T(KC_S), RCTL_T(KC_MINUS),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,    KC_MPLY,          KC_NO,   KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                              SCMD(KC_R), LT(1, KC_SPC), LT(1, KC_SPC),       LT(2, KC_ENT), LT(2, KC_ENT), LCMD(A(KC_I))
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET  , DEBUG,   _______, _______, _______, _______,                            _______, _______, _______, _______, DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_END,  KC_HOME, _______,                            _______, LALT(KC_LEFT), LALT(KC_RIGHT), _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_DOWN, KC_UP,   _______,                            _______, KC_LEFT, KC_RIGHT, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______,          _______, _______, WORD_L,  WORD_R,  _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_EXLM, KC_AT,   KC_HASH, KC_DOLLAR, KC_PERCENT, KC_CIRC,                       KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                               KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRACKET, KC_RBRACKET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, RCMD_T(KC_SLASH), RALT_T(KC_EQL), RSFT_T(KC_BSLASH), RCTL_T(KC_GRAVE), _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, RESET,            RESET, _______, KC_QUES, KC_PLUS, KC_PIPE, KC_TILDE, _______,
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
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
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
    }
    else if (index == 1) {
        if (!cmd_held) {
            cmd_held = true;
            register_code(KC_LGUI);
        }

        cmd_timer = timer_read();

        if (clockwise) {
            tap_code16(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    }
    return true;
}

void matrix_scan_user(void) {
    if (cmd_held && timer_elapsed(cmd_timer) >= CMD_TIMEOUT) {
        unregister_code(KC_LGUI);
        cmd_held = false;
        cmd_timer = 0;
    }
}
