#include QMK_KEYBOARD_H
#include "print.h"

#define _DVORAK 0
#define _SYM 1
#define _NAV 2
#define _MOD_L 3
#define _MOD_R 4

#define KUNO_REFRESH    SCMD(KC_R)
#define KUNO_DEVTOOLS   LCMD(A(KC_I))
#define KUNO_EMOJI      LCTL(LCMD(KC_SPC))

enum custom_keycodes {
  HOLD_MIN = (SAFE_RANGE | 0x0f) + 1,
  HOLD_MAX = HOLD_MIN + 0x10,
  WORD_L,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
  PAGE_B,  // emacs backward-page, C-X [
  PAGE_F,  // emacs forward-page, C-X ]
  DROP,
};

#define HOLD(layer) (HOLD_MIN | ((layer)&0x0F))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, KUNO_REFRESH,                 KUNO_DEVTOOLS, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPACE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LPRN, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,    KC_MPLY,       KUNO_EMOJI, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RPRN,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  KC_SPC, HOLD(_MOD_L),         HOLD(_MOD_R), KC_ENT, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPACE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  S(KC_LBRC), KC_LBRC, S(KC_4), KC_RBRC, S(KC_RBRC),                     S(KC_SLASH), KC_SLASH, KC_EQL, KC_BSLS, S(KC_BSLS), KC_KP_PLUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  S(KC_1), S(KC_2), S(KC_3), S(KC_GRAVE), S(KC_5), RESET,         RESET, S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            PAGE_B,  WORD_L,  KC_UP,   WORD_R,  KC_PGUP, KC_HOME,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            PAGE_F,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_END,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MOD_L] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      DROP,    DROP,   TO(_NAV), TO(_SYM), DROP,   DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      DROP,    KC_LOPT, KC_LCMD, KC_LSFT, KC_LCTL, DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      DROP,    DROP,    DROP,    DROP,    DROP,    DROP,    DROP,             DROP,    DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     DROP,    DROP,   _______,                   _______,  DROP,    DROP
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MOD_R] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    DROP,   TO(_SYM), TO(_NAV), DROP,   DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      DROP,    DROP,    DROP,    DROP,    DROP,    DROP,                               DROP,    KC_RCTL, KC_RSFT, KC_RCMD, KC_ROPT, DROP,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      DROP,    DROP,    DROP,    DROP,    DROP,    DROP,    DROP,             DROP,    DROP,    DROP,    DROP,    DROP,    DROP,    DROP,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     DROP,    DROP,   _______,                   _______,  DROP,    DROP
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

};

static uint8_t warp_hold_active = 0;

bool process_drop(uint16_t keycode, keyrecord_t *record) {
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

    case HOLD_MIN ... HOLD_MAX:
        if (record->event.pressed) {
            uint8_t layer = keycode & 0x0F;
            layer_on(layer);
            uprintf("HOLD is active. Switching to layer 0x%02X.  Mods are 0x%02X\n", layer, get_mods());
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

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if (clockwise) {
            backlight_increase();
        } else {
            backlight_decrease();
        }
    }

    return true;
}

void keyboard_post_init_keymap(void) {
#if BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(3);
#endif
}
