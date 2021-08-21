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

#define KW_SPACE   LT(_LOWER, KC_SPC)
#define KW_ENTER   LT(_RAISE, KC_ENT)


enum custom_keycodes {
  UNUSED = SAFE_RANGE,
  WORD_L,  // emacs word left (ESC, B)
  WORD_R,  // emacs word right (ESC, F)
  PAGE_B,  // emacs backward-page, C-X [
  PAGE_F,  // emacs forward-page, C-X ]
};

bool process_emacs_nav(uint16_t keycode, keyrecord_t *record);
