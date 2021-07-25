#include QMK_KEYBOARD_H
#include "print.h"

#define _DVORAK 0
#define _NAV 1
#define _NUM 2
#define _SYSTEM 3

#define KUNO_REFRESH    SCMD(KC_R)
#define KUNO_DEVTOOLS   LCMD(A(KC_I))
#define KUNO_EMOJI      LCTL(LCMD(KC_SPC))

enum custom_keycodes {
  WORD_L = SAFE_RANGE,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_ESC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTRL, KC_A,   KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,    KC_MPLY,       KUNO_EMOJI, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LOPT, KC_LCMD, LT(_NAV, KC_SPC),  LT(_NUM, KC_ENT), KC_RCMD, KC_ROPT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET,  DEBUG,    _______, _______, _______, KUNO_REFRESH,                 KUNO_DEVTOOLS, _______, _______, _______, DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_INS,  WORD_L,  KC_UP,   WORD_R,  KC_PGUP,                            KC_INS,  WORD_L,  KC_UP,   WORD_R,  KC_PGUP, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN,                           KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_HOME, _______, KC_END,  _______, _______,          _______, _______, KC_HOME,  _______, KC_END, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET,  DEBUG,    _______, _______, _______, KUNO_REFRESH,                 KUNO_DEVTOOLS, _______, _______, _______, DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     S(KC_GRAVE), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                        S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_EQL),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, S(KC_LBRC), KC_LBRC, KC_RBRC, S(KC_RBRC), _______,    _______,  S(KC_SLASH), KC_SLASH, KC_BSLS, S(KC_BSLS), _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

};

bool process_emacs_nav(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case WORD_L:
        // Emacs word left (ESC, B)
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC)"b");
        }
        return false;
        break;

    case WORD_R:
        // Emacs word right (ESC, F)
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC)"f");
        }
        return false;
        break;

    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_emacs_nav(keycode, record);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if (IS_LAYER_ON(_NUM)) {
            if (clockwise) {
                tap_code16(KC_MS_WH_UP);
            } else {
                tap_code16(KC_MS_WH_DOWN);
            }
        } else {
            if (clockwise) {
                backlight_increase();
            } else {
                backlight_decrease();
            }
        }
    }

    return true;
}

void keyboard_post_init_keymap(void) {
#if BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(5);
#endif
}
