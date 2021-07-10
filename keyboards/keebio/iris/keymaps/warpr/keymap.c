#include QMK_KEYBOARD_H
#include "print.h"

#define _DVORAK 0
#define _NUM 1
#define _LMODS 2
#define _RMODS 3
// #define _SYSTEM 3

#define KUNO_REFRESH    SCMD(KC_R)
#define KUNO_DEVTOOLS   LCMD(A(KC_I))
#define KUNO_EMOJI      LCTL(LCMD(KC_SPC))

enum custom_keycodes {
  WARP_LEFT_MODS_MIN = (SAFE_RANGE | 0x0f) + 1,
  WARP_LEFT_MODS_MAX = WARP_LEFT_MODS_MIN + 0x10,
  WARP_RIGHT_MODS_MIN,
  WARP_RIGHT_MODS_MAX = WARP_RIGHT_MODS_MIN + 0x10,
  WORD_L,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
};

/*

WARP_LEFT_MOD(layer)
- When pressed, switches to specified layer (which should have only
  the four modifiers for a single hand)
- As soon as a modifier is pressed, that modifier is registered.
- When the modifier is physically released, the modifier remains held.
- If any further modifiers are pressed, they also remain held.
- If a non-modifier key is pressed, the modifier layer is turned off.
- Modifiers remain held until the WARP_LEFT_MOD() key is released.

*/

#define WARP_L(layer) (WARP_LEFT_MODS_MIN | ((layer)&0x0F))
#define WARP_R(layer) (WARP_RIGHT_MODS_MIN | ((layer)&0x0F))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE, KC_QUOT, KC_COMM, KC_DOT, KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_ESC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_SCOLON, KC_Q,  KC_J,    KC_K,    KC_X,    KC_MPLY,       KUNO_EMOJI, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                             _______, WARP_L(_LMODS), LT(_NUM, KC_SPC),  LT(_NUM, KC_SPC), WARP_R(_RMODS), _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET,  DEBUG,    _______, _______, _______, KUNO_REFRESH,                 KUNO_DEVTOOLS, _______, _______, _______, DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_HOME, KC_SLASH, KC_EQL, KC_BSLS, _______,                            _______, KC_7,    KC_8,    KC_9,    KC_0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, WORD_L,  WORD_R,  KC_LBRC, KC_RBRC, KC_PGUP,                            _______, KC_4,    KC_5,    KC_6,    KC_0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_END,  _______, S(KC_9), S(KC_0), KC_PGDN, _______,          _______, _______, KC_1,    KC_2,    KC_3,    KC_0,    _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LMODS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LOPT, KC_LCMD, KC_LSFT, KC_LCTRL, _______,                           _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RMODS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_RCTRL,KC_RSFT, KC_RCMD, KC_ROPT, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

/*
  [_SYSTEM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______,                            _______, KC_SYSREQ, KC_SLCK, KC_PAUSE, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______,                            _______, KC_INS,  KC_HOME, KC_PGUP, _______, DEBUG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,          _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, RESET,
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

static uint8_t warp_left_layer_held = 0;
static uint8_t warp_left_mods_held = 0;
static uint8_t warp_right_layer_held = 0;
static uint8_t warp_right_mods_held = 0;

void debug_warp_mods(uint16_t keycode, keyrecord_t *record) {
    uprintf(
        "WARP MODS: kc: 0x%04X, pressed: %b, layer held: 0x%04X, mods held: 0x%04X\n",
        keycode,
        record->event.pressed,
        warp_left_layer_held,
        warp_left_mods_held
    );
}

bool process_warp_mods(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_LCTRL ... KC_LGUI:
        if (record->event.pressed) {
            if (warp_left_layer_held) {
                warp_left_mods_held = warp_left_mods_held | MOD_BIT(keycode);

                uprintf("LEFT MOD ACTIVATED: 0x%04X, current mods: 0x%04X\n", MOD_BIT(keycode), warp_left_mods_held);
            }
        } else {
            if (warp_left_layer_held) {
                // don't unregister this key press
                return false;
            }
        }
        break;
    case KC_RCTRL ... KC_RGUI:
        if (record->event.pressed) {
            if (warp_right_layer_held) {
                warp_right_mods_held = warp_right_mods_held | MOD_BIT(keycode);

                uprintf("RIGHT MOD ACTIVATED: 0x%04X, current mods: 0x%04X\n", MOD_BIT(keycode), warp_right_mods_held);
            }
        } else {
            if (warp_right_layer_held) {
                // don't unregister this key press
                return false;
            }
        }
        break;
    case WARP_LEFT_MODS_MIN ... WARP_LEFT_MODS_MAX:
        if (record->event.pressed) {
            uint8_t layer = keycode & 0x0F;
            layer_on(layer);
            warp_left_layer_held = layer;
            uprintf("WARP LEFT MOD LAYER ENGAGED!\n");
            return false;
        } else {
            if (warp_left_layer_held) {
                layer_off(warp_left_layer_held);
                warp_left_layer_held = 0;
            }

            // clear_mods(warp_left_mods_held);
            clear_mods();
            for (uint8_t i = 0; i < 8; i++) {
                if (warp_left_mods_held & MOD_BIT(KC_LCTRL + i)) {
                    uprintf("[LEFT] need to unregister %04X\n", KC_LCTRL + i);
                    unregister_code(KC_LCTRL + i);
                }
            }

            warp_left_mods_held = 0;
            uprintf("WARP LEFT MODS CLEARED!\n");
            return false;
        }
        break;
    case WARP_RIGHT_MODS_MIN ... WARP_RIGHT_MODS_MAX:
        if (record->event.pressed) {
            uint8_t layer = keycode & 0x0F;
            layer_on(layer);
            warp_right_layer_held = layer;
            uprintf("WARP RIGHT MOD LAYER ENGAGED!\n");
            return false;
        } else {
            if (warp_right_layer_held) {
                layer_off(warp_right_layer_held);
                warp_right_layer_held = 0;
            }

            // clear_mods(warp_right_mods_held);
            clear_mods();
            for (uint8_t i = 0; i < 8; i++) {
                if (warp_right_mods_held & MOD_BIT(KC_RCTRL + i)) {
                    uprintf("[RIGHT] need to unregister %04X\n", KC_RCTRL + i);
                    unregister_code(KC_RCTRL + i);
                }
            }

            warp_right_mods_held = 0;
            uprintf("WARP RIGHT MODS CLEARED!\n");
            return false;
        }
        break;
    default:
        // any other key breaks out of the modifier layer, so the modifiers
        // can be combined with other keys as long as the layer key is still held.
        if (warp_left_layer_held) {
            layer_off(warp_left_layer_held);
            warp_left_layer_held = 0;
            uprintf("WARP LEFT MOD LAYER CLEARED!\n");
            debug_warp_mods(keycode, record);
        }
        if (warp_right_layer_held) {
            layer_off(warp_right_layer_held);
            warp_right_layer_held = 0;
            uprintf("WARP RIGHT MOD LAYER CLEARED!\n");
            debug_warp_mods(keycode, record);
        }
        break;
    }

    if (warp_left_layer_held) {
        set_mods(warp_left_mods_held);
        debug_warp_mods(keycode, record);
    }
    if (warp_right_layer_held) {
        set_mods(warp_right_mods_held);
        debug_warp_mods(keycode, record);
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_warp_mods(keycode, record)
        && process_emacs_nav(keycode, record);
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
