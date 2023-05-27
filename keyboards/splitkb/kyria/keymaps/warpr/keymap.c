/**
 * Copyright 2019  Thomas Baart <thomas@splitkb.com>
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
#define KW_ENTER   LT(_RAISE, KC_ENT)

#define KW_XTRA    MO(_ADJUST)

#define KC_BSPACE  KC_BACKSPACE

enum custom_keycodes {
    DEL_SPC = SAFE_RANGE,  // emacs M-\, delete-horizontal-space
    SPACE_4,               // fake tab (four spaces)
    BSPC_4,                // backspace fake tab (four spaces)
    DEL_4,                 // del fake tab (four spaces)
};

enum layers {
    _DVORAK = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT(
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                                            KC_F,    KC_G,    KC_C,    KC_R,   KC_L,    KC_ESC,
        KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                                            KC_D,    KC_H,    KC_T,    KC_N,   KC_S,    KC_MINUS,
        SC_LSPO, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KW_FRSH, KW_EMOJ,    KW_MOOM, KW_DEVT,  KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,    SC_RSPC,
                                   KC_DEL,  KW_WINB, KC_LCMD, KW_SPC,  KC_LCTL,    KC_RCTL, KW_ENTER, KC_ROPT, KW_WINF, KC_BSPACE
    ),

    [_LOWER] = LAYOUT(
        SPACE_4, KC_PGUP, WORD_L,  KC_UP,   WORD_R,  KC_HOME,                                        _______, KC_7,    KC_8,    KC_9,   _______,  DEL_SPC,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                         _______, KC_4,    KC_5,    KC_6,   _______,  _______,
        _______, _______, _______, KW_SCR3, KW_SCR4, KW_SCR5, _______, QK_BOOT,    _______, KC_0,    _______, KC_1,    KC_2,    KC_3,   _______,  _______,
                                   DEL_4,   _______, _______, _______, _______,    _______, KC_0,    _______, _______, BSPC_4
    ),

    [_RAISE] = LAYOUT(
        SPACE_4, KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_VOLU,                                        _______, KC_AMPR, KC_ASTR, KC_PLUS, _______, DEL_SPC,
        KC_LCBR, KC_CIRC, KC_GRV,  KC_TILD, KC_DLR,  KC_VOLD,                                        KC_QUES, KC_SLSH, KC_EQL,  KC_BSLS, KC_PIPE, KC_RCBR,
        KC_LBRC, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KW_XTRA, _______,    QK_BOOT, _______, DEL_SPC, _______, _______, _______, _______, KC_RBRC,
                                   DEL_4,   _______, _______, KW_XTRA, _______,    _______, _______, _______, _______, BSPC_4
    ),

    [_ADJUST] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                                        KC_INS,  KC_PSCR, KC_SCRL, KC_PAUS, _______, _______,
        _______, KC_F5,   KC_F6,   KC_F7 ,  KC_F8,   _______,                                        _______, _______, _______, _______, _______, _______,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KW_XTRA, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, KW_XTRA, _______,    _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case DEL_SPC:
        // Emacs M-\, delete-horizontal-space
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC) "\\");
        }
        return false;

    case SPACE_4:
        // Fake tab (four spaces)
        if (record->event.pressed) {
            SEND_STRING("    ");
        }
        return false;

    case BSPC_4:
        // Backspace fake tab (four spaces)
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE));
        }
        return false;

    case DEL_4:
        // Del fake tab (four spaces)
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_DEL) SS_TAP(X_DEL) SS_TAP(X_DEL) SS_TAP(X_DEL));
        }
        return false;
    }

    return true;
}
