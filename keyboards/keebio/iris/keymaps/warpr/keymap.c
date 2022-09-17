/**
 * Copyright 2021  Kuno Woudt <kuno@frob.nl>
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
#include "print.h"

#define KW_FRSH    SCMD(KC_R)          // browser refresh
#define KW_DEVT    LCMD(A(KC_I))       // browser dev tools
#define KW_EMOJ    LCTL(LCMD(KC_SPC))  // macos emoji picker
#define KW_MOOM    LCTL(LCMD(KC_M))    // moom window management
#define KW_WINF    LCMD(KC_GRAVE)      // cmd+` (macos, next window of current app)
#define KW_WINB    LCMD(KC_TILDE)      // cmd+~ (macos, prev window of current app)

#define WORD_L     LALT(KC_LEFT)       // alt+left (word left, macos/emacs)
#define WORD_R     LALT(KC_RIGHT)      // alt+right (word right, macos/emacs)

#define KW_SCR3    SCMD(KC_3)          // screenshot (macos)
#define KW_SCR4    SCMD(KC_4)          // screenshot (region, macos)
#define KW_SCR5    SCMD(KC_5)          // screenshot (window/etc..., macos)

#define KW_SPC     LT(_LOWER, KC_SPC)
#define KW_TAB     LT(_RAISE, KC_TAB)
#define KW_ENT     LT(_RAISE, KC_ENT)

#define KW_XTRA    MO(_ADJUST)

/**
 * Combos
 * ======
 */
enum combo_events {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_BACKSPACE,
    COMBO_LCBR, // {
    COMBO_RCBR, // }
    COMBO_LPRN, // (
    COMBO_RPRN, // )
    COMBO_LBRC, // [
    COMBO_RBRC, // ]
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_esc[] = {KC_QUOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM combo_backspace[] = {KC_R, KC_L, COMBO_END};
const uint16_t PROGMEM combo_lcbr[] = {KC_DOT, KC_P, COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM combo_lbrc[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_rcbr[] = {KC_G, KC_C, COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_M, KC_W, COMBO_END};

combo_t key_combos[] = {
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_BACKSPACE] = COMBO(combo_backspace, KC_BACKSPACE),
    [COMBO_LCBR] = COMBO(combo_lcbr, KC_LCBR),
    [COMBO_LPRN] = COMBO(combo_lprn, KC_LPRN),
    [COMBO_LBRC] = COMBO(combo_lbrc, KC_LBRC),
    [COMBO_RCBR] = COMBO(combo_rcbr, KC_RCBR),
    [COMBO_RPRN] = COMBO(combo_rprn, KC_RPRN),
    [COMBO_RBRC] = COMBO(combo_rbrc, KC_RBRC),
};

/**
 * Layers
 * ======
 */

enum layers {
    _DVORAK = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT(
        _______, _______, _______, _______, _______, KW_FRSH,                    KW_DEVT, _______, _______, _______, _______, _______,
        KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    _______,                    _______, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
        KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    _______,                    _______, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,
        KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______, KC_MPLY,  KW_EMOJ, _______, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,
                                            KC_LCMD, KC_LCTL, KW_SPC,   KW_ENT,  KC_RSFT, KC_ROPT
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        KC_PGUP, WORD_L,  KC_UP,   WORD_R,  KC_HOME, _______,                    _______, KC_LCBR, KC_7,    KC_8,    KC_9,    KC_RCBR,
        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,                    _______, KC_LPRN, KC_4,    KC_5,    KC_6,    KC_RPRN,
        _______, KC_DEL,  KW_SCR3, KW_SCR4, KW_SCR5, _______, RESET,    RESET,   _______, KC_LBRC, KC_1,    KC_2,    KC_3,    KC_RBRC,
                                            KC_LCMD, KC_LCTL, KW_SPC,   KC_0,    KC_RSFT, KC_ROPT
    ),

    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_ESC,  _______,                  _______, KC_BSPACE, KC_AMPR, KC_ASTR, KC_PLUS, KC_QUES,
        KC_CIRC, KC_GRV,  KC_TILD, KC_DLR,  KC_TAB,  _______,                   _______, KC_MINUS, KC_SLSH, KC_EQL,  KC_BSLS, KC_PIPE,
        _______, _______, KW_EMOJ, KW_FRSH, KW_DEVT, _______, RESET,    RESET,   _______, _______, KW_MOOM, KW_WINF, KW_WINB, _______,
                                            _______, _______, KW_XTRA,  _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______,                    _______, KC_INS,  KC_PSCR, KC_SLCK, KC_PAUS, _______,
        KC_F5,   KC_F6,   KC_F7 ,  KC_F8,   _______, _______,                    _______, _______, _______, _______, _______, _______,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, KW_XTRA,  _______, _______, _______
    )
};

void keyboard_post_init_keymap(void) {
#if BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(5);
#endif
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
