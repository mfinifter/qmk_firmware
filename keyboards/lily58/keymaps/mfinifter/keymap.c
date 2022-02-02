#include QMK_KEYBOARD_H
#include <stdio.h>

char wpm_str[10];

enum layer_number {
  _DVORAK = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DVORAK 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  DEL |BackSP| LGUI | /Lower, /       \Raise,\  | RCTRL| RAlt | BSLSH|
 *                   |      |      |      |/ Space /         \ Enter\ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_DVORAK] = LAYOUT(
   KC_GRV,    KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                                              KC_6,    KC_7,    KC_8, KC_9, KC_0, KC_EQL,
   KC_TAB, KC_QUOT, KC_COMM, KC_DOT,    KC_P,    KC_Y,                                              KC_F,    KC_G,    KC_C, KC_R, KC_L, KC_SLSH,
   KC_ESC,    KC_A,    KC_O,   KC_E,    KC_U,    KC_I,                                              KC_D,    KC_H,    KC_T, KC_N, KC_S, KC_MINS,
  KC_LSFT, KC_SCLN,    KC_Q,   KC_J,    KC_K,    KC_X,            KC_LBRC,              KC_RBRC,    KC_B,    KC_M,    KC_W, KC_V, KC_Z, KC_RSFT,
                             KC_DEL, KC_BSPC, KC_LGUI, LT(_LOWER, KC_SPC),   LT(_RAISE, KC_ENT), KC_RCTL, KC_RALT, KC_BSLS
),

[_LOWER] = LAYOUT(
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_PIPE,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     MO(3), KC_TRNS, KC_TRNS, KC_TRNS
),
[_RAISE] = LAYOUT(
   KC_GRV,    KC_1,    KC_2, KC_3,       KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,     KC_9,    KC_0,  KC_EQL,
   KC_GRV,    KC_1,    KC_2, KC_3,       KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,     KC_9,    KC_0,  KC_EQL,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_PGUP, KC_TRNS,   KC_UP,  KC_TRNS, KC_TRNS, KC_HOME,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS,  KC_END,
                             KC_TRNS,  KC_DEL, KC_TRNS,   MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
  [_ADJUST] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,     KC_F4,     KC_F5,     KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,
  KC_TRNS, KC_TRNS, KC_TRNS,   MEH(KC_V), KC_TRNS,   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, LSA(KC_J), MEH(KC_C), LSA(KC_P), KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                               KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

const char *read_layer_state(void);
const char *read_logo(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_ln(read_layer_state(), false);
    oled_write_ln_P(PSTR(""), false);
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write(wpm_str, false);
    oled_write_P(PSTR(" wpm"), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
#endif
  }
  return true;
}
