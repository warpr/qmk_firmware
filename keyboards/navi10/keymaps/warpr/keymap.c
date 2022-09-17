/* Copyright 2019 Ethan Durrant (emdarcher)
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

#define INDICATOR_LED   B5

/* Define layer names */
enum userspace_layers {
    _MAIN  = 0,
    _ALT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_ESC,   KC_UP,    LT(_ALT, KC_ENTER),
        KC_LEFT,  KC_DOWN,  KC_RIGHT,

        /* -- */  KC_MPLY,
        KC_VOLD,  KC_MUTE,  KC_VOLU
    ),
    [_ALT] = LAYOUT(
        KC_NO,    KC_EJCT,  KC_TRNS,
        KC_MPRV,  KC_MSTP,  KC_MNXT,

        /* -- */  RESET,
        KC_MRWD,  KC_MSEL,  KC_MFFD
    )
};

void keyboard_pre_init_user(void) {
    writePinHigh(INDICATOR_LED);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _ALT:
        writePinLow(INDICATOR_LED);
        break;
    default:
        writePinHigh(INDICATOR_LED);
        break;
    }

    return state;
}
