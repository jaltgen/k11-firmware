/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

enum layers{
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    FN2,
};


// tap dance umlaut functions
// idea is to follow this manual and https://docs.qmk.fm/#/feature_tap_dance
// register on one function per umlaut to register an KC_ALTGR and A/Y/O/S which
// when the OS is set to US intl. will produce umlaute. same f
// the same can eventually be used for things likme []{};: etc../
// or we use KEY_OVERRIDE_ENABLE = yes  - see here https://docs.qmk.fm/#/feature_key_overrides

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};


// Tap Dance declarations
enum {
    TD_WIN_OUML_P,
    TD_WIN_AUML_Q,
    TD_WIN_UUML_Y,
    TD_WIN_SZLIG_S,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    // used for Umlaut in Win US Intl. keymap.
    [TD_WIN_OUML_P] = ACTION_TAP_DANCE_DOUBLE(KC_O, RALT(KC_P)),
    [TD_WIN_AUML_Q] = ACTION_TAP_DANCE_DOUBLE(KC_A, RALT(KC_Q)),
    [TD_WIN_UUML_Y] = ACTION_TAP_DANCE_DOUBLE(KC_U, RALT(KC_Y)),
    [TD_WIN_SZLIG_S] = ACTION_TAP_DANCE_DOUBLE(KC_S, RALT(KC_S)),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_G,    KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_BSPC, KC_A,     KC_R,     KC_S,    KC_T,    KC_D,              KC_H,    KC_N,    KC_E,    KC_I,     KC_O,  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_K,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPTN, KC_LCMMD,          LT(MAC_FN1,KC_SPC),           MO(MAC_FN1), MO(FN2),        LT(MAC_FN1,KC_SPC),            KC_RCMMD,           KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_G,    KC_J,     KC_L,    TD(TD_WIN_UUML_Y),    KC_Y,    KC_SCLN,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_BSPC, TD(TD_WIN_AUML_Q),  KC_R,     TD(TD_WIN_SZLIG_S),    KC_T,    KC_D,              KC_H,    KC_N,    KC_E,    KC_I,     TD(TD_WIN_OUML_P),  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_K,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LWIN,  KC_LALT,  LT(WIN_FN1,KC_SPC),           MO(WIN_FN1), MO(FN2),       LT(WIN_FN1,KC_SPC),            KC_RALT,            KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN1] = LAYOUT_69_ansi(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
        _______, BT_HST1,  KC_HOME,  KC_UP, KC_END, _______, _______,  _______, _______, _______, KC_INS,   KC_PGUP,  _______,  _______,          _______,
        KC_BSPC, RGB_TOG,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_ENTER,           _______, _______, _______, KC_SNAP,  KC_PGDN,  KC_END,   _______,          _______,
        _______,           RGB_MOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [WIN_FN1] = LAYOUT_69_ansi(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FILE, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
        _______, BT_HST1,  KC_HOME,  KC_UP, KC_END, _______, _______,  _______, _______, _______, KC_INS,   KC_PGUP,  _______,  _______,          _______,
        KC_BSPC, RGB_TOG,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_ENTER,           _______, _______, _______, KC_PSCR,  KC_PGDN,  KC_END,   _______,          _______,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [FN2] = LAYOUT_69_ansi(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, BAT_LVL,  BAT_LVL, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            DT_UP, DT_PRNT, DT_DOWN),

    // [GAME] = LAYOUT_69_ansi(
    //     KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
    //     KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Z,     KC_L,    TD(TD_WIN_UUML_Y),    KC_Y,    KC_SCLN,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
    //     KC_BSPC, TD(TD_WIN_AUML_Q),     KC_R,     TD(TD_WIN_SZLIG_S),    KC_T,    KC_D,              KC_H,    KC_N,    KC_E,    KC_I,     TD(TD_WIN_OUML_P),  KC_QUOT,  KC_ENT,           KC_HOME,
    //     KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_K,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
    //     KC_LCTL, KC_LWIN,  TD(TD_ALT_FN),           LT(WIN_FN1,KC_SPC),           MO(WIN_FN1), MO(FN2),       LT(WIN_FN1,KC_SPC),            KC_RALT,            KC_LEFT, KC_DOWN, KC_RGHT),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [FN2]      = { ENCODER_CCW_CW(_______, _______)},
};
#endif // ENCODER_MAP_ENABLE
