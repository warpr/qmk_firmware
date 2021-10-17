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
#include "warpr.h"

#define LAYOUT_wrapper(...)      LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_wrapper(
      ____DVORAK_L0____,                    ____DVORAK_R0____,
      ____DVORAK_L1____,                    ____DVORAK_R1____,
      ____DVORAK_L2____,                    ____DVORAK_R2____,
      ____DVORAK_L3____, KC_MPLY,  KW_EMOJ, ____DVORAK_R3____,
      ____DVORAK_L4____,                    ____DVORAK_R4____
    ),

    [_LOWER] = LAYOUT_wrapper(
      ____LOWER__L0____,                    ____LOWER__R0____,
      ____LOWER__L1____,                    ____LOWER__R1____,
      ____LOWER__L2____,                    ____LOWER__R2____,
      ____LOWER__L3____, RESET,    RESET,   ____LOWER__R3____,
      ____LOWER__L4____,                    ____LOWER__R4____
    ),

    [_RAISE] = LAYOUT_wrapper(
      ____RAISE__L0____,                    ____RAISE__R0____,
      ____RAISE__L1____,                    ____RAISE__R1____,
      ____RAISE__L2____,                    ____RAISE__R2____,
      ____RAISE__L3____, RESET,    RESET,   ____RAISE__R3____,
      ____RAISE__L4____,                    ____RAISE__R4____
    ),

    [_ADJUST] = LAYOUT_wrapper(
      ____ADJUST_L0____,                    ____ADJUST_R0____,
      ____ADJUST_L1____,                    ____ADJUST_R1____,
      ____ADJUST_L2____,                    ____ADJUST_R2____,
      ____ADJUST_L3____, _______,  _______, ____ADJUST_R3____,
      ____ADJUST_L4____,                    ____ADJUST_R4____
    ),
};

/* uint32_t layer_state_set_user(uint32_t state) { */
/*     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); */
/* } */

void keyboard_post_init_keymap(void) {
#if BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(5);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_warpr(keycode, record);
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
