/**
 * Copyright 2021      Kuno Woudt <kuno@frob.nl>     @warpr
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

/* Define layer names */
enum userspace_layers {
    _DVORAK  = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define KW_FRSH    SCMD(KC_R)          // browser refresh
#define KW_DEVT    LCMD(A(KC_I))       // browser dev tools
#define KW_EMOJ    LCTL(LCMD(KC_SPC))  // macos emoji picker
#define KW_MOOM    LCTL(LCMD(KC_M))    // moom window management

#define WORD_L     LALT(KC_LEFT)       // alt+left (word left, macos/emacs)
#define WORD_R     LALT(KC_RIGHT)      // alt+right (word right, macos/emacs)

#define KW_SHOT3   SCMD(KC_3)          // screenshot (macos)
#define KW_SHOT4   SCMD(KC_4)          // screenshot (region, macos)
#define KW_SHOT5   SCMD(KC_5)          // screenshot (window/etc..., macos)

#define KW_SPACE   LT(_LOWER, KC_SPC)
#define KW_ENTER   LT(_RAISE, KC_ENT)

bool process_record_warpr(uint16_t keycode, keyrecord_t *record);

// See: https://discord.com/channels/440868230475677696/473506116718952450/862166415619391498
// for wrapper info

#define ____DVORAK_L0____  _______,  _______,  _______,  _______,  _______,  KW_FRSH
#define ____DVORAK_L1____  KC_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,     KC_Y
#define ____DVORAK_L2____  KC_LCTL,  KC_A,     KC_O,     KC_E,     KC_U,     KC_I
#define ____DVORAK_L3____  KC_LSPO,  KC_SCOLON, KC_Q,    KC_J,     KC_K,     KC_X

#define ____DVORAK_R0____  KW_DEVT,  _______,  _______,  _______,  _______,  _______
#define ____DVORAK_R1____  KC_F,     KC_G,     KC_C,     KC_R,     KC_L,     KC_ESC
#define ____DVORAK_R2____  KC_D,     KC_H,     KC_T,     KC_N,     KC_S,     KC_MINUS
#define ____DVORAK_R3____  KC_B,     KC_M,     KC_W,     KC_V,     KC_Z,     KC_RSPC

#define ____LOWER__L0____  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6
#define ____LOWER__L1____  KC_GRAVE, KC_1,     KC_2,     KC_3,     KC_4,     KC_5
#define ____LOWER__L2____  KC_LCBR,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC
#define ____LOWER__L3____  KC_LBRC,  _______,  _______,  _______,  KC_TILD,  KC_SPACE

#define ____LOWER__R0____  KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12
#define ____LOWER__R1____  KC_6,     KC_7,     KC_8,     KC_9,       KC_0,     KC_BSPACE
#define ____LOWER__R2____  KC_QUES,  KC_SLASH, KC_EQL,   KC_BSLASH,  KC_PIPE,  KC_RCBR
#define ____LOWER__R3____  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_KP_PLUS, _______,  KC_RBRC

#define ____RAISE__L0____  _______, _______, _______, _______, _______, _______
#define ____RAISE__L1____  _______, RESET,   _______, KW_SHOT3, KW_SHOT4, KW_SHOT5
#define ____RAISE__L2____  _______, _______, _______, _______, _______, _______
#define ____RAISE__L3____  _______, _______, _______, _______, _______, _______

#define ____RAISE__R0____  _______, _______, _______, _______, _______, _______
#define ____RAISE__R1____  KC_PGUP, WORD_L,  KC_UP,   WORD_R,  KC_HOME, KC_BSPACE
#define ____RAISE__R2____  KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, _______
#define ____RAISE__R3____  KC_PENT, KW_MOOM, KC_DEL,  KC_BSPC, _______, _______

#define ____ADJUST_L0____  _______, _______, _______, _______, _______, _______
#define ____ADJUST_L1____  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______
#define ____ADJUST_L2____  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______
#define ____ADJUST_L3____  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______

#define ____ADJUST_R0____  _______, _______, _______, _______, _______, _______
#define ____ADJUST_R1____  KC_INS,  KC_PSCR, KC_SLCK, KC_PAUS, _______, _______
#define ____ADJUST_R2____  _______, _______, _______, _______, _______, _______
#define ____ADJUST_R3____  _______, _______, _______, _______, _______, RESET
