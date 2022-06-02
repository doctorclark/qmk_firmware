/* Edited version from an original that was Copyright 2021 bitstarr
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

/*-----------------------
DDC Edits:
Mod-Tap https://docs.qmk.fm/#:~:text=Leader%20Key-,Mod%2DTap,-Macros to make Left-Shift act as
a shift key when held, but act as a Capslock key when pressed.

Mouse buttons require
*** "MOUSEKEY_ENABLE = yes" in rules.mk ***

Unicode requires
*** "UNICODE_ENABLE = yes" to rules.mk ***
*** "#define UNICODE_SELECTED_MODES UC_WINC" to config.h ***

Tap dance requires
*** "TAP_DANCE_ENABLE = yes" to rules.mk ***
*** "#define TAPPING_TERM 175" to config.h ***
*** "#define TAPPING_TOGGLE 2" to config.h ***

RGB experiment based on https://docs.qmk.fm/#/feature_rgb_matrix resulted in no progress--this board uses RGB Lights, NOT matrix
------------------------*/

#include QMK_KEYBOARD_H
#define H(x) UC(0x##x) // I don't fully understand *how* this works, but it does.

enum layers {
	_BASE,
    _NUMPAD,
	_PLAYER
};


/*```LED numbers on board
,-----------------------------------------------------------------------.
|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  | 11  |
|-----------------------------------------------------------------------+
|  12   | 13  | 14  | 15  | 16  | 17  | 18  | 19  | 20  | 21  |   22    |
|-----------------------------------------------------------------------+
|     23    | 24  | 25  | 26  | 27  | 28  | 29  | 30  | 31  | 32  | 33  |
|-----------------------------------------------------------------------+
| 34  | 35  | 36  |       37       |     38     | 39  | 40  | 41  | 42  |
`-----------------------------------------------------------------------'
Under:     48        47       46        45       44        43
```*/

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_TEAL},      // Light 10 LEDs, starting with LED 1, this is q through p
    {13, 9, HSV_TEAL},      // Light 9 LEDs, starting with LED 9, this is a through l
    {24, 7, HSV_TEAL}       // Light 7 LEDs, starting with LED 24, this is z through m
);
// Light LEDs XXX when keyboard layer 1 is active LAYER 1 OF LED, LAYER 0 of board!
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS( // _BASE
	{0, 1, HSV_RED},		// this is Esc
	{43, 6, HSV_DKORANGE}		// this is t to test dkoarange on key
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS( // _NUMPAD
    {35, 2, HSV_RED},       // this is LWIN and LALT
    {6, 6, HSV_RED},       // this is y through del
    {18, 5, HSV_RED},       // this is h through ent
    {28, 6, HSV_RED},       // this is b through rbrace
	{11, 1, HSV_RED},		// this is DEL
    {7, 3, HSV_WHITE},		// this is u, i, o = 789
	{19, 3, HSV_WHITE},		// this is jkl = 456
	{29, 3, HSV_WHITE},		// this is nm, = 123
	{32, 1, HSV_DKORANGE}		// this is up
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS( // _PLAYER
    {1, RGBLED_NUM, HSV_PURPLE},       // this is the whole board
    {37, 2, HSV_RED},       // this is spacebars, the ms buttons 1 and 2
	{0, 1, HSV_YELLOW}, // this is the reset button
	{2, 1, HSV_AZURE}, // this is w as scroll up
	{4, 1, HSV_BLUE}, 	// this is r as boot
	{1, 1, HSV_ORANGE}, // this is q to make it ms button 3, scroll!
	{35, 2, HSV_YELLOW}, // this is ms buttons 4 and 5
	{32, 1, HSV_WHITE}, // this is up arrow as pgup
	{40, 3, HSV_WHITE}, // this is arrows as home, pgdown, end
	{13, 3, HSV_AZURE}, // this is asd as the other scrolls
	{7, 3, HSV_GREEN},		// this is u, i, o = 789
	{19, 3, HSV_GREEN},		// this is jkl = 456
	{29, 2, HSV_GREEN}		// this is nm, = 123
);	

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer, // DDC this is called differently from the actual layers. Capslock here is the *LED* base layer
	my_layer0_layer, // DDC this is called differently than the actual layers. This is LED layer 1 but is actual layer 0, the _BASE layer
    my_layer1_layer, // DDC this is actual layer 2 on the keymap, but is later called as "layer 2" for the lighting layer. _NUMPAD
	my_layer2_layer // DDC this will be the play layer, _PLAYER
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}


bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUMPAD));
	rgblight_set_layer_state(3, layer_state_cmp(state, _PLAYER));
    return state;
}


// Tap Dance declarations
enum {
    TD_EGRV,
    TD_BOOT
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Grave
    [TD_EGRV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
    [TD_BOOT] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B) // TD_BOOT experiment did not work, only basic keycodes work with tap dance, not QK_BOOT
};

// MACROS https://docs.qmk.fm/#/feature_macros
enum custom_keycodes {
    DDCURL = SAFE_RANGE,
    DDC_OM,
	CTL_A = LT(10, KC_A), // Tap for a, hold to select all
	CTL_C = LT(10, KC_C), // Tap for c, hold to copy
	CTL_N = LT(10, KC_N), // Tap for n, hold for new doc
	CTL_P = LT(10, KC_P), // Tap for p, hold to print
	CTL_S = LT(10, KC_S), // Tap for s, hold to save
    CTL_X = LT(10, KC_X), // Tap for x, hold to cut
	CTL_V = LT(10, KC_V), // Tap for v, hold to paste
    CTL_Y = LT(10, KC_Y), // Tap for y, hold to redo
    CTL_Z = LT(10, KC_Z), // Tap for z, hold to undo
	VHLDBT, // 
	CADEL // Tap for delete, hold for CTL+ALT+DEL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CADEL:
        if (record->tap.count && record->event.pressed) { 
                tap_code16(KC_DEL); //tap action 
            } else if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_DEL)SS_UP(X_LCTL)SS_UP(X_LALT)SS_UP(X_DEL));	// hold action 
            } 
            return false; 
    case CTL_C:
        if (record->tap.count && record->event.pressed) { 
                tap_code16(KC_C); //tap action 
            } else if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c")); // hold action 
            } 
            return false; 
    case CTL_V:
        if (record->tap.count && record->event.pressed) { 
                tap_code16(KC_V); //tap action 
            } else if (record->event.pressed) {
                SEND_STRING(SS_LCTL("v")); // hold action 
            } 
            return false;
    case CTL_X:
        if (record->tap.count && record->event.pressed) { 
                tap_code16(KC_X); //tap action 
            } else if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x")); // hold action 
            } 
            return false; 
    case CTL_Z:
        if (record->tap.count && record->event.pressed) { 
                tap_code16(KC_Z); //tap action 
            } else if (record->event.pressed) {
                SEND_STRING(SS_LCTL("z")); // hold action 
            } 
            return false; 
    case CTL_Y:
        if (record->tap.count && record->event.pressed) { 
                tap_code16(KC_Y); //tap action 
            } else if (record->event.pressed) {
                SEND_STRING(SS_LCTL("y")); // hold action 
            } 
            return false; 
    case DDCURL:
        if (record->event.pressed) {
            // when keycode DDCURL is pressed
            SEND_STRING("https://ddc.me/\n");
        } else {
            // when keycode DDCURL is released
        }
        break;
 
    case DDC_OM:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("ac")); // selects all and copies
        }
        break;
    }
    return true;
};



/*```
,-----------------------------------------------------------------------.
|EGRV |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bscp |
|-----------------------------------------------------------------------+
| Tab   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Enter  |
|-----------------------------------------------------------------------+
|Shift/Caps |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  UP |  .  |
|-----------------------------------------------------------------------+
|Ctrl | Win | Alt |      TTL1     |    Space    |TTL2 | LT  |  DN | RT  |
`-----------------------------------------------------------------------'
```*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        TD(TD_EGRV),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   CTL_Y,    KC_U,    KC_I,    KC_O,   CTL_P,    KC_BSPC,
        KC_TAB,    	CTL_A,   CTL_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_ENT,
        LSFT_T(KC_CAPS),   CTL_Z,    CTL_X,    CTL_C,    CTL_V,    KC_B,   CTL_N,    KC_M,    KC_COMM,   KC_UP,    KC_DOT,
        KC_LCTL, KC_LGUI, KC_LALT,    TT(_NUMPAD),              KC_SPC,       TT(_PLAYER), KC_LEFT,   KC_DOWN,  KC_RGHT
    ),
    [_NUMPAD] = LAYOUT(
        TO(_BASE),   RGB_TOG, RGB_VAD, RGB_VAI, _______, _______,  KC_MINS, KC_7,  KC_8,  	KC_9,  	KC_0, 	 KC_DEL,
        _______,       _______,  DDCURL,  DDC_OM, _______, _______, KC_SCLN, KC_4,     KC_5,    KC_6,     KC_EQL,
        _______,        _______,      _______, CTL_C,   CTL_V,    KC_QUOT,  KC_1,   KC_2,   KC_3,  KC_PAST,  KC_SLSH,
        _______, KC_BTN1, KC_BTN2,     _______,                 KC_0,            KC_DOT,  KC_PPLS, KC_PMNS,  KC_ENT
    ),
    [_PLAYER] = LAYOUT(
        TO(_BASE), KC_BTN3, KC_WH_U, KC_J, QK_BOOT, KC_VOLD,  KC_VOLU,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   CADEL,
        H(3B1),      KC_WH_L, KC_WH_D, KC_WH_R, _______, _______, _______,    KC_F4,   KC_F5,   KC_F6,      KC_BSLS,
		_______,        _______,   _______,   _______,  _______,  KC_MUTE,    KC_F1, KC_F2, KC_LBRC, KC_PGUP, KC_RBRC,
        _______, KC_BTN4, KC_BTN5,  KC_BTN1,              KC_BTN2,            _______,      KC_HOME, KC_PGDN, KC_END
    ),
	
};
