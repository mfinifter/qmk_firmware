/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

// Ideas:
// * window management / desktop switching / application switching
// * zoom mute / face mute
// * web browser: scrolling, changing tabs, nav back/forward
// /
// https://www.reddit.com/r/olkb/comments/bauj0t/can_you_change_encoders_output_using_layers_qmk/
// talks about making encoders do different things on different layers
//
// https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder- talks
// about setting up command-tabbing for application switching
//
// all layers have a key to switch to layer 0, layer 1, layer 2
//
// layer 0: navigation, web browsing, and VC
//   encoder 0:
//   encoder 1:
//   encoder 2:
// layer 1: application management
//   encoder 0: virtual desktop switching
//   encoder 1: app switching 
//   encoder 2: tab switching
// layer 2: window management
//   encoder 0: shrink/grow master pane
//     press: cycle layout
//   encoder 1: select active window
//   encoder 2: move active window counter-clockwise / clockwise
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        KC_MUTE, KC_HOME, KC_MPLY,
        MO(1)  , KC_UP  , RGB_MOD,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) { // scroll word left/right
        if (clockwise) {
            tap_code16(LALT(KC_RGHT));
        } else {
            tap_code16(LALT(KC_LEFT));
        }
    }
    else if (index == _MIDDLE) { // mouse wheel up / down
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    else if (index == _RIGHT) { // window management: shrink / expand master pane
        if (clockwise) {
            tap_code16(LSA(KC_P));
        } else {
            tap_code16(LSA(KC_J));
        }
    }
    return true;
}
