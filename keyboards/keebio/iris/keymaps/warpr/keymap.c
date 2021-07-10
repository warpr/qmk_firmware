#include QMK_KEYBOARD_H
#include "print.h"

#define _DVORAK 0
#define _NUM 1
#define _SYSTEM 2

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
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_ESC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTRL, KC_A,   KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,    KC_MPLY,       KUNO_EMOJI, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                 KC_LOPT, KC_LCMD, LT(_NUM, KC_SPC),       LT(_NUM, KC_ENT), KC_RCMD, KC_ROPT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET,  DEBUG,    _______, _______, _______, KUNO_REFRESH,                 KUNO_DEVTOOLS, _______, _______, _______, DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_HOME, S(KC_LBRC), KC_SLASH, S(KC_RBRC),  KC_PGUP,                    _______, KC_7,    KC_8,    KC_9,    KC_PLUS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, WORD_L,  KC_LBRC, KC_EQL,  KC_RBRC, WORD_R,                             KC_0,    KC_1,    KC_2,    KC_3,    KC_0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_END,  S(KC_9), KC_BSLS, S(KC_0), KC_PGDN, _______,          _______, KC_COMMA, KC_4,   KC_5,    KC_6,    KC_DOT,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
/*
  [_SYSTEM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                            _______, KC_SYSREQ, KC_SLCK, KC_PAUSE, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,                            _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,          _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
*/
};

static bool emacs_backspace_held = false;
static bool emacs_down_held = false;
static bool emacs_left_held = false;
static bool emacs_right_held = false;
static bool emacs_up_held = false;

bool process_emacs_nav(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_P:
        if (record->event.pressed) {
            // if CTRL+P is pressed, send up arrow instead
            // NOTE: just CTRL, so e.g. CTRL+ALT doesn't count
            // NOTE: Left CTRL only, so Right CTRL sends plain CTRL+P
            if (get_mods() == MOD_BIT(KC_LCTRL)) {
                del_mods(MOD_BIT(KC_LCTRL));
                register_code(KC_UP);
                emacs_up_held = true;
                set_mods(MOD_BIT(KC_LCTRL));
                return false;
            }
        } else {
            if (emacs_up_held) {
                unregister_code(KC_UP);
                emacs_up_held = false;
                return false;
            }
        }
        break;

    case KC_N:
        if (record->event.pressed) {
            if (get_mods() == MOD_BIT(KC_LCTRL)) {
                del_mods(MOD_BIT(KC_LCTRL));
                register_code(KC_DOWN);
                emacs_down_held = true;
                set_mods(MOD_BIT(KC_LCTRL));
                return false;
            }
        } else {
            if (emacs_down_held) {
                unregister_code(KC_DOWN);
                emacs_down_held = false;
                return false;
            }
        }
        break;

    case KC_B:
        if (record->event.pressed) {
            if (get_mods() == MOD_BIT(KC_LCTRL)) {
                del_mods(MOD_BIT(KC_LCTRL));
                register_code(KC_LEFT);
                emacs_left_held = true;
                set_mods(MOD_BIT(KC_LCTRL));
                return false;
            }
        } else {
            if (emacs_left_held) {
                unregister_code(KC_LEFT);
                emacs_left_held = false;
                return false;
            }
        }
        break;

    case KC_F:
        if (record->event.pressed) {
            if (get_mods() == MOD_BIT(KC_LCTRL)) {
                del_mods(MOD_BIT(KC_LCTRL));
                register_code(KC_RIGHT);
                emacs_right_held = true;
                set_mods(MOD_BIT(KC_LCTRL));
                return false;
            }
        } else {
            if (emacs_right_held) {
                unregister_code(KC_RIGHT);
                emacs_right_held = false;
                return false;
            }
        }
        break;

    case KC_H:
        if (record->event.pressed) {
            if (get_mods() == MOD_BIT(KC_LCTRL)) {
                del_mods(MOD_BIT(KC_LCTRL));
                register_code(KC_BSPACE);
                emacs_backspace_held = true;
                set_mods(MOD_BIT(KC_LCTRL));
                return false;
            }
        } else {
            if (emacs_backspace_held) {
                unregister_code(KC_BSPACE);
                emacs_backspace_held = false;
                return false;
            }
        }
        break;

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
