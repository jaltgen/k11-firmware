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
} td_state_t;



const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!}
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
        case 0:
        //mac
            rgb_matrix_set_color_all(RGB_MAC);
            for (uint8_t i = led_min; i < led_max; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                    rgb_matrix_set_color(i, RGB_CARROT);
                }
                rgb_matrix_set_color(1, RGB_MAC);
            }
            return true;
        break;
        case 1:
        //win
            rgb_matrix_set_color_all(RGB_WINDOWS);
            for (uint8_t i = led_min; i < led_max; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                    rgb_matrix_set_color(i, RGB_CARROT);
                }
                rgb_matrix_set_color(1, RGB_ROSE);
            }
            return true;
        break;
        case 2:
        //mac fn
            rgb_matrix_set_color_all(RGB_CARROT);
            for (uint8_t i = led_min; i < led_max; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                    rgb_matrix_set_color(i, RGB_MAC);
                }
                rgb_matrix_set_color(1, RGB_MAC);
            }
            return true;
        break;
        case 3:
        //win fnoooo
            rgb_matrix_set_color_all(RGB_CARROT);
            for (uint8_t i = led_min; i < led_max; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                    rgb_matrix_set_color(i, RGB_WINDOWS);
                rgb_matrix_set_color(1, RGB_ROSE);
                }
            }
            return true;
        break;
        case 4:
        //win fn
            rgb_matrix_set_color_all(RGB_CARROT);
            for (uint8_t i = led_min; i < led_max; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                    rgb_matrix_set_color(i, RGB_CARROT);
                }
            }
            return true;
        break;
        default:
            return true;
    };
};

// // // //
enum custom_keycodes {
    MAC_OUML,
};

// Instead implementing it a s funcions on my FN2 layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool shift_held     = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
    bool alt_held       = get_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT));
    switch (keycode) {
        case MAC_OUML:
            if (record->event.pressed) {
                if (alt_held){
                    if (shift_held) {
                        // holding alt
                        register_code(KC_LALT);
                        // adding  four  hex symbols
                        register_code(KC_0);
                        unregister_code(KC_0);
                        register_code(KC_0);
                        unregister_code(KC_0);
                        register_code(KC_D);
                        unregister_code(KC_D);
                        register_code(KC_6);
                        unregister_code(KC_6);
                        //and release the alt key
                        unregister_code(KC_LALT);
                        return false;
                    } else {
                        // holding alt
                        register_code(KC_LALT);
                        // adding  four  hex symbols
                        register_code(KC_0);
                        unregister_code(KC_0);
                        register_code(KC_0);
                        unregister_code(KC_0);
                        register_code(KC_F);
                        unregister_code(KC_F);
                        register_code(KC_6);
                        unregister_code(KC_6);
                        //and release the alt key
                        unregister_code(KC_LALT);
                        return false;
                    }// Place your custom function code here
                }
            }
            return true; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}


// The best approach may be to use unicode, which is a super simple keyboard layout in Mac ("Unicode Hex Input"), taht works well with my Colemak, and also supports Alt codes as documented here.
// https://www.webnots.com/4-ways-to-type-accented-letters-in-mac/

// void mac_ouml_func(tap_dance_state_t *state, void *user_data) {
//     if (state->count >= 3) {

//            // Check if Shift is held down
//         // Check if Shift is held down
//         bool shift_held = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
//         if (shift_held) {
//             // holding alt
//             register_code(KC_LALT);
//             // adding  four  hex symbols
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_D);
//             unregister_code(KC_D);
//             register_code(KC_6);
//             unregister_code(KC_6);
//             //and release the alt key
//             unregister_code(KC_LALT);
//         } else {
//             // holding alt
//             register_code(KC_LALT);
//             // adding  four  hex symbols
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_F);
//             unregister_code(KC_F);
//             register_code(KC_6);
//             unregister_code(KC_6);
//             //and release the alt key
//             unregister_code(KC_LALT);
//         }

//     }

//     switch (state->count) {
//         case 1:
//             register_code(KC_O);
//             unregister_code(KC_O);
//             reset_tap_dance(state);
//     }
// }
// void mac_auml_func(tap_dance_state_t *state, void *user_data) {
//     if (state->count >= 3) {

//            // Check if Shift is held down
//         // Check if Shift is held down
//         bool shift_held = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
//         if (shift_held) {
//             // holding alt
//             register_code(KC_LALT);
//             // adding  four  hex symbols
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_C);
//             unregister_code(KC_C);
//             register_code(KC_4);
//             unregister_code(KC_4);
//             //and release the alt key
//             unregister_code(KC_LALT);
//         } else {
//             // holding alt
//             register_code(KC_LALT);
//             // adding  four  hex symbols
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_E);
//             unregister_code(KC_E);
//             register_code(KC_4);
//             unregister_code(KC_4);
//             //and release the alt key
//             unregister_code(KC_LALT);
//         }

//     }

//     switch (state->count) {
//         case 1:
//             register_code(KC_A);
//             unregister_code(KC_A);
//             reset_tap_dance(state);
//     }
// }
// void mac_uuml_func(tap_dance_state_t *state, void *user_data) {
//     if (state->count >= 3) {

//            // Check if Shift is held down
//         // Check if Shift is held down
//         bool shift_held = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
//         if (shift_held) {
//             // holding alt
//             register_code(KC_LALT);
//             // adding  four  hex symbols
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_D);
//             unregister_code(KC_D);
//             register_code(KC_C);
//             unregister_code(KC_C);
//             //and release the alt key
//             unregister_code(KC_LALT);
//         } else {
//             // holding alt
//             register_code(KC_LALT);
//             // adding  four  hex symbols
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_0);
//             unregister_code(KC_0);
//             register_code(KC_F);
//             unregister_code(KC_F);
//             register_code(KC_C);
//             unregister_code(KC_C);
//             //and release the alt key
//             unregister_code(KC_LALT);
//         }

//     }

//     switch (state->count) {
//         case 1:
//             register_code(KC_U);
//             unregister_code(KC_U);
//             reset_tap_dance(state);
//     }
// }
// void mac_szlig_func(tap_dance_state_t *state, void *user_data) {
//     if (state->count >= 3) {


//         register_code(KC_LALT);
//         // adding  four  hex symbols
//         register_code(KC_0);
//         unregister_code(KC_0);
//         register_code(KC_0);
//         unregister_code(KC_0);
//         register_code(KC_D);
//         unregister_code(KC_D);
//         register_code(KC_F);
//         unregister_code(KC_C);
//         //and release the alt key
//         unregister_code(KC_LALT);


//     }

//     switch (state->count) {
//         case 1:
//             register_code(KC_S);
//             unregister_code(KC_S);
//             reset_tap_dance(state);
//     }
// }
// // Tap Dance declarations
enum {
    TD_ALT_FN,
    TD_WIN_OUML_P,
    TD_WIN_AUML_Q,
    TD_WIN_UUML_Y,
    // TD_MAC_OUML_O,
    // TD_MAC_AUML_A,
    // TD_MAC_UUML_U,
    // TD_MAC_SZLIG_S,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    // used for Umlaut in Win US Intl. keymap.
    [TD_ALT_FN] = ACTION_TAP_DANCE_DOUBLE(OSL(4), KC_LALT),
    [TD_WIN_OUML_P] = ACTION_TAP_DANCE_DOUBLE(KC_O, RALT(KC_P)),
    [TD_WIN_AUML_Q] = ACTION_TAP_DANCE_DOUBLE(KC_A, RALT(KC_Q)),
    [TD_WIN_UUML_Y] = ACTION_TAP_DANCE_DOUBLE(KC_U, RALT(KC_Y)),
    // [TD_MAC_OUML_O] = ACTION_TAP_DANCE_FN(mac_ouml_func),
    // [TD_MAC_AUML_A] = ACTION_TAP_DANCE_FN(mac_auml_func),
    // [TD_MAC_UUML_U] = ACTION_TAP_DANCE_FN(mac_uuml_func),
    // [TD_MAC_SZLIG_S] = ACTION_TAP_DANCE_FN(mac_szlig_func),
};



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_G,    KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_BSPC, KC_A,     KC_R,     KC_S,    KC_T,    KC_D,              KC_H,    KC_N,    KC_E,    KC_I,      KC_O,  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_K,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPTN, KC_LCMMD,          LT(MAC_FN1,KC_SPC),           MO(MAC_FN1), MO(FN2),        LT(MAC_FN1,KC_SPC),            KC_RCMMD,           KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,             KC_0,    KC_MINS,     KC_EQL,             KC_BSPC,  KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_G,              KC_J,    KC_L,    TD(TD_WIN_UUML_Y),KC_Y,    KC_SCLN,     KC_LBRC,            KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_BSPC, TD(TD_WIN_AUML_Q),  KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,             KC_E,    KC_I,        TD(TD_WIN_OUML_P),  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_K,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LWIN,  KC_LALT,           LT(MAC_FN1,KC_SPC),           MO(MAC_FN1), MO(FN2),       LT(MAC_FN1,KC_SPC),            KC_RALT,            KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN1] = LAYOUT_69_ansi(
        KC_GRV,  BT_HST1,  BT_HST2,  BT_HST3, KC_LPAD, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
        _______, BT_HST1,  KC_HOME,  KC_UP, KC_END, _______,                _______,          KC_7, KC_8, KC_9, KC_INS,   KC_PGUP,  _______,  _______,          _______,
        KC_BSPC, RGB_TOG,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_ENTER,           _______,          KC_4, KC_5, KC_6, KC_PGDN,  KC_END,   _______,          _______,
        _______,           RGB_MOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,     _______, NK_TOGG, KC_1, KC_2, KC_3,  KC_DOT,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [WIN_FN1] = LAYOUT_69_ansi(
        KC_GRV,  BT_HST1,  BT_HST2,  BT_HST3, KC_FILE, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
        _______, BT_HST1,  KC_HOME,  KC_UP, KC_END, _______, _______,                KC_7, KC_8, KC_9, KC_INS,   KC_PGUP,  _______,  _______,          _______,
        KC_BSPC, RGB_TOG,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_ENTER,           _______, KC_4, KC_5, KC_6,  KC_PGDN,  KC_END,   _______,          _______,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, NK_TOGG, KC_1, KC_2, KC_3,  KC_DOT,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [FN2] = LAYOUT_69_ansi(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, BAT_LVL,  BAT_LVL, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            DT_UP, DT_PRNT, DT_DOWN),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [FN2]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    };
#endif // ENCODER_MAP_ENABLE

