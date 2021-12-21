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
// https://www.reddit.com/r/olkb/comments/bauj0t/can_you_change_encoders_output_using_layers_qmk/
// talks about making encoders do different things on different layers
//
// https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder- talks
// about setting up command-tabbing for application switching
//
// layer 0: window management
//   encoder 0: shrink/grow master pane
//     press: cycle layout
//   encoder 1: select active window
//     press: move active window to master pane
//   encoder 2: move active window counter-clockwise / clockwise
//     press: move active window to other screen
//   minimize / full-screen toggle / close window
//   hold for adjust layer / go to layer 1 / go to layer 2
// layer 1: navigation, web browsing, and zoom
//   encoder 0: mouse wheel up/down
//     press: home
//   encoder 1: mouse wheel left/right
//     press: end
//   encoder 2: browser tab left/right
//     press: close tab
//   mute / face mute / start/stop screen share
//   go to layer 0 / nothing / go to layer 2
// layer 2: text editing
//   encoder 0: scroll word at a time
//     press: cut
//   encoder 1: left/right
//     press: copy
//   encoder 2: up/down
//     press: paste
//   shift/backspace/delete
//   go to layer 0 / go to layer 1 / nothing
// layer ADJUST: reset / rgb control
//   encoder 0: increase/decrease hue
//    press: toggle lighting on/off
//   encoder 1: increase/decrease saturation
//    press: cycle through modes forward
//   encoder 2: increase/decrease brightness
//    press: cycle through modes backward
//   bl toggle / bl step / bl breathing
//   nothing / nothing / reset
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LALT(KC_SPACE), LSA(KC_ENTER), MEH(KC_J),
        LGUI(KC_M), LGUI(LCTL(KC_F)), LGUI(KC_W),
        MO(3), TO(1), TO(2)
    ),
    [1] = LAYOUT(
        KC_HOME, KC_END, LGUI(KC_W),
        LSG(KC_A), LSG(KC_V), LSG(KC_S),
        TO(0), KC_TRNS, TO(2)
    ),
    [2] = LAYOUT(
        LGUI(KC_X), LGUI(KC_C), LGUI(KC_V),
        KC_LEFT_SHIFT, KC_BACKSPACE, KC_DELETE,
        TO(0), TO(1), KC_TRNS
    ),
    [3] = LAYOUT(
        RGB_TOG, RGB_MODE_FORWARD, RGB_MODE_REVERSE,
        BL_TOGG, BL_STEP, BL_BRTG,
        KC_TRNS, KC_TRNS, RESET
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
