/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Elliot Powell <@e11i0t23>
Copyright 2021 Matt Gemmell <@mattgemmell>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// this change was made from the Github website
#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_REDO LSFT(LGUI(KC_Z))
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_MAC_LOCK_SCRN LCTL(LGUI(KC_Q))
#define KC_MAC_SCRN_SHOT LGUI(LSFT(KC_3))
#define KC_MAC_SCRN_MRKP LGUI(LSFT(KC_4))
#define KC_MAC_HOME LGUI(KC_UP)
#define KC_MAC_END LGUI(KC_DOWN)
#define KC_MAC_PREV_TAB LGUI(LSFT(KC_LBRACKET))
#define KC_MAC_NEXT_TAB LGUI(LSFT(KC_RBRACKET))
#define KC_MAC_SPOTLIGHT LGUI(KC_SPC)
#define KC_N_DASH LALT(KC_MINUS)
#define KC_M_DASH LSFT(LALT(KC_MINUS))
#define KC_EURO LALT(KC_2)
#define KC_HTAG_WIN KC_NUHS
#define KC_HTAAG_MAC LALT(KC_3)
#define KC_STERLING LSFT(KC_3)
#define KC_LOGIN C(A(KC_DEL))
//#define MKC_SCLN KC_SCLN
//#define MKC_COLON LSFT(KC_SCLN)
#define MKC_QMARK LSFT(KC_SLSH)

//#define PW M(YOUR_MACRO_1)

#define ___off___	{0,0,0}
#define MG__WHITE	{255,255,255}
#define	MG____RED	{255,0,0}
#define MG__GREEN	{32,159,33}
#define MG___BLUE	{0,181,213}
#define MG_YELLOW	{255,208,0}
#define MG_ORANGE	{255,85,0}
#define MG___PINK	{208,0,255}
#define MG_PURPLE	{50,0,232}

// Tap Dance declarations
enum {
    TD_PIPE,
    TD_SLASHES,
    TD_SEMICOLON,
    TD_COLON,
    TD_PARENS,
    TD_LTGT,
    TD_BRACES,
    TD_BRAKETS,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PIPE] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_BSLS), LSFT(KC_BSLS)),
    [TD_SLASHES] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_SLSH),
    [TD_SEMICOLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_SCLN),
    [TD_COLON] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_SCLN), LSFT(KC_SCLN)),
    [TD_PARENS] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_9), LSFT(KC_0)),
    [TD_LTGT] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_COMM), LSFT(KC_DOT)),
    [TD_BRACES] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_LBRC), LSFT(KC_RBRC)),
    [TD_BRAKETS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};



// Layer Declarations
enum my_layers {
    _BASE,
    _CURSOR,
    _SYMBOLS,
    _NUMPAD,
    _MOUSE,
    _FNKEYS,
    _SYSTEM,
};

//enum custom_keycodes {
//    PW = SAFE_RANGE,
//};

// Oneshot keycode Declarations
enum my_keycodes {
    // Callum oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    //OS_CAPS, // for use as Globe on iPadOS, via remapping in Settings.app
    OS_HYPR,
    APP_SWITCH_FRWD, // cmd-tab but holds cmd between invocations
    PW,
    PIPE,
    SEMICOLON,
    COLON,
    SEMI_COLON,
};


#define BSPC_CURSOR LT(_CURSOR, KC_BSPC)

//#define EDIT MO(_EDIT)
//#define NUM MO(_NUM)
//#define NUMB TG(_NUM)
#define CURSOR TG(_CURSOR)
#define SYMBOLS MO(_SYMBOLS)
#define NUMPAD MO(_NUMPAD) 
#define MOUSE MO(_MOUSE)
#define FNKEYS MO(_FNKEYS)
#define SYSTEM MO(_SYSTEM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        XXXXXXX,    KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,       KC_J,           KC_L,           KC_U,       KC_Y,       KC_QUOT,       XXXXXXX,
        XXXXXXX,    KC_A,   KC_R,   KC_S,   KC_T,   KC_G,       KC_M,           KC_N,           KC_E,       KC_I,       KC_O,          XXXXXXX,
        XXXXXXX,    KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,       KC_K,           KC_H,           KC_COMM,    KC_DOT,     MKC_QMARK,     XXXXXXX,
                                            MOUSE,  OS_SHFT,    KC_SPC,         BSPC_CURSOR,    SYMBOLS,    NUMPAD
  ),

    [_CURSOR] = LAYOUT_split_3x6_3(
        XXXXXXX,    KC_ESC,         KC_TAB,     KC_MAC_PREV_TAB,    KC_MAC_NEXT_TAB,    XXXXXXX,            KC_PGUP,        KC_MAC_PREV_TAB,  KC_UP,           KC_MAC_NEXT_TAB, KC_BSPC,    XXXXXXX,
        XXXXXXX,    OS_SHFT,        OS_CTRL,    OS_ALT,             OS_CMD,             OS_HYPR,            KC_PGDOWN,      KC_LEFT,          KC_DOWN,         KC_RIGHT,        XXXXXXX,    MOUSE,
        XXXXXXX,    KC_MAC_UNDO,    KC_MAC_CUT, KC_MAC_COPY,        KC_MAC_PASTE,       KC_MAC_REDO,        KC_MAC_HOME,    KC_MAC_SPOTLIGHT, APP_SWITCH_FRWD, XXXXXXX,         KC_MAC_END, XXXXXXX,
                                                _______,           _______,             KC_ENT,             BSPC_CURSOR,    _______,          _______
  ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        XXXXXXX,    KC_ESC,         KC_TAB,     KC_MS_BTN1,         KC_MS_BTN2,     XXXXXXX,        KC_MS_WH_UP,        KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_MAC_LOCK_SCRN,   XXXXXXX,
        XXXXXXX,    OS_SHFT,        OS_CTRL,    OS_ALT,             OS_CMD,         OS_HYPR,        KC_MS_WH_DOWN,      KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    XXXXXXX,            MOUSE,
        XXXXXXX,    KC_MAC_UNDO,    KC_MAC_CUT, KC_MAC_COPY,        KC_MAC_PASTE,   KC_MAC_REDO,    KC_MAC_HOME,        KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_MAC_END,         XXXXXXX,
                                                _______,            _______,        _______,        _______,            _______,        _______
  ),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
        XXXXXXX,    KC_EXLM,    KC_AT,      KC_PERC,        KC_CIRC,        KC_AMPR,        TD(TD_PIPE),    TD(TD_SLASHES), TD(TD_SEMICOLON),   TD(TD_COLON),   KC_BSPC,        XXXXXXX,
        XXXXXXX,    KC_EURO,    KC_DLR,     KC_STERLING,    KC_HTAG_WIN,    KC_HTAAG_MAC,   TD(TD_PARENS),  TD(TD_LTGT),    KC_PAST,            KC_PMNS,        LSFT(KC_MINS),  XXXXXXX,
        XXXXXXX,    KC_N_DASH,  KC_M_DASH,  LSFT(KC_QUOT),  KC_QUOT,        KC_TILDE,       TD(TD_BRACES),  TD(TD_BRAKETS), KC_PSLS,            KC_PPLS,        KC_PEQL,        XXXXXXX,
                                            _______,        _______,        _______,        _______,        _______,        _______
  ),
  

    [_NUMPAD] = LAYOUT_split_3x6_3(
        XXXXXXX,    KC_ESC,     KC_TAB,     KC_LPRN,    KC_RPRN,    KC_PDOT,        KC_PAST,    KC_7,       KC_8,       KC_9,       KC_PMNS,    XXXXXXX,
        XXXXXXX,    OS_SHFT,    OS_CTRL,    OS_ALT,     OS_CMD,     OS_HYPR,        KC_PSLS,    KC_4,       KC_5,       KC_6,       KC_PPLS,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_0,       KC_1,       KC_2,       KC_3,       KC_PEQL,    XXXXXXX,
                                            KC_LOGIN,   PW,         _______,        _______,    _______,    _______
  ),


    [_FNKEYS] = LAYOUT_split_3x6_3(
        XXXXXXX,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,          KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,     XXXXXXX,
        XXXXXXX,    OS_SHFT,    OS_CTRL,    OS_ALT,     OS_CMD,     OS_HYPR,        OS_HYPR,    OS_CMD,     OS_ALT,     OS_CTRL,    OS_SHFT,    XXXXXXX,
        XXXXXXX,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,         KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,     XXXXXXX,
                                            _______,    _______,    _______,        _______,    _______,    _______
  ),

    [_SYSTEM] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, KC_AUDIO_VOL_DOWN,    KC_AUDIO_MUTE,          KC_AUDIO_VOL_UP,        XXXXXXX,    KC_MAC_SCRN_SHOT,   KC_MAC_SCRN_MRKP,   XXXXXXX,    XXXXXXX,    KC_MAC_LOCK_SCRN,   XXXXXXX,
        XXXXXXX, OS_SHFT, OS_CTRL,              OS_ALT,                 OS_CMD,                 XXXXXXX,    XXXXXXX,            XXXXXXX,            XXXXXXX,    XXXXXXX,    KC_BRIGHTNESS_UP,   XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,    XXXXXXX,    XXXXXXX,            XXXXXXX,            XXXXXXX,    XXXXXXX,    KC_BRIGHTNESS_DOWN, XXXXXXX,
                                                _______,                _______,                _______,    _______,            _______,            _______
  ),

};

const uint8_t PROGMEM ledmap[][42][3] = {
/* Starts at layer 1; we don't apply lights to Base (layer 0). */
[_BASE] = {
MG____RED, ___off___, ___off___, ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___, ___off___, ___off___, MG____RED,
___off___, ___off___, ___off___, ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___, ___off___, ___off___, ___off___,
MG_ORANGE, ___off___, ___off___, ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___, ___off___, ___off___, MG___BLUE,
								 ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___
			},

[_CURSOR] = {
MG____RED, MG____RED, MG_ORANGE, MG___PINK, MG___PINK, ___off___, 				MG_ORANGE, MG___PINK, MG__WHITE, MG___PINK, MG____RED, MG____RED,
MG____RED, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG_PURPLE, 				MG_ORANGE, MG__WHITE, MG__WHITE, MG__WHITE, ___off___, MG____RED,
MG____RED, MG___PINK, MG__GREEN, MG__GREEN, MG__GREEN, MG___PINK, 				MG_ORANGE, MG_YELLOW, MG_PURPLE, ___off___, MG_ORANGE, MG____RED,
								 MG___BLUE, MG___BLUE, MG____RED, 				___off___, ___off___, MG__GREEN
			},
            
[_MOUSE] = {
MG__GREEN, MG____RED, MG_ORANGE, MG___PINK, MG___PINK, ___off___, 				MG_ORANGE, MG___PINK, MG__WHITE, MG___PINK, ___off___, MG__GREEN,
MG__GREEN, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG_PURPLE, 				MG_ORANGE, MG__WHITE, MG__WHITE, MG__WHITE, ___off___, MG__GREEN,
MG__GREEN, MG___PINK, MG__GREEN, MG__GREEN, MG__GREEN, MG___PINK, 				MG_ORANGE, MG_YELLOW, MG_YELLOW, MG_YELLOW, MG_ORANGE, MG__GREEN,
								 ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___
			},

[_SYMBOLS] = {
MG_PURPLE, MG__GREEN, MG__GREEN, MG__GREEN, MG__GREEN, MG__GREEN, 				MG___PINK, MG___PINK, MG__GREEN, MG__GREEN, MG____RED, MG_PURPLE,
MG_PURPLE, MG_ORANGE, MG_ORANGE, MG_ORANGE, MG_ORANGE, MG_ORANGE, 				MG___PINK, MG___PINK, MG_YELLOW, MG_YELLOW, MG___BLUE, MG_PURPLE,
MG_PURPLE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, 				MG___PINK, MG___PINK, MG_YELLOW, MG_YELLOW, MG_PURPLE, MG_PURPLE,
						   		 ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___
			},

[_NUMPAD] = {
MG___BLUE, MG____RED, MG_ORANGE, MG_PURPLE, MG_PURPLE, MG_ORANGE, 				MG_YELLOW, MG__GREEN, MG__GREEN, MG__GREEN, MG_YELLOW, MG___BLUE,
MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, 				MG_YELLOW, MG__GREEN, MG__GREEN, MG__GREEN, MG_YELLOW, MG___BLUE,
MG___BLUE, ___off___, ___off___, ___off___, ___off___, MG___BLUE, 				MG__GREEN, MG__GREEN, MG__GREEN, MG__GREEN, MG_PURPLE, MG___BLUE,
						   		 MG___BLUE, MG___BLUE, MG___BLUE, 				MG___BLUE, MG___BLUE, MG___BLUE
			},
[_FNKEYS] = {
MG_YELLOW, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, 				MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_YELLOW,
MG_YELLOW, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, 				MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, MG_YELLOW,
MG_YELLOW, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, 				MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_PURPLE, MG_YELLOW,
								 ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___
			},
[_SYSTEM] = {
MG_ORANGE, ___off___, MG_PURPLE, MG____RED, MG_PURPLE, ___off___, 				MG___PINK, MG___PINK, ___off___, ___off___, MG____RED, MG_ORANGE,
MG_ORANGE, MG___BLUE, MG___BLUE, MG___BLUE, MG___BLUE, ___off___, 				___off___, ___off___, ___off___, ___off___, MG_YELLOW, MG_ORANGE,
MG_ORANGE, ___off___, MG_YELLOW, MG_YELLOW, MG_YELLOW, ___off___, 				___off___, ___off___, ___off___, ___off___, MG_YELLOW, MG_ORANGE,
								 ___off___, ___off___, ___off___, 				___off___, ___off___, ___off___
			},

};


extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_sethsv_noeeprom(0, 0, 0); // (180, 255, 231) is purple
    rgb_matrix_mode_noeeprom(1);
}

// ====================================================
// RGB matrix
// ====================================================

uint8_t ledIndexForKeymapIndex(uint8_t keyIndex) {
	// Turn keyIndex into a row and column within g_led_config.
	// Reference: https://github.com/qmk/qmk_firmware/blob/master/keyboards/crkbd/r2g/r2g.c
	uint8_t row = 0;
	uint8_t col = 0;
	uint8_t keysPerRow = 12; // Specific to crkdb!
	uint8_t keysPerHalf = keysPerRow / 2; // Assumes equal split!

	row = keyIndex / keysPerRow;
	col = keyIndex % keysPerRow;
	if (row == 3) { // Specific to crkbd!
		col += 3; // Compensate for leading three NO_LED entries in g_led_config.
	}

	bool mirror = (col >= keysPerHalf);
	if (mirror) {
		// Normalise row and col per g_led_config structure.
		row += 4;
		col -= keysPerHalf;
		// Mirror column position.
		col = (keysPerHalf - 1) - col;
	}

	return g_led_config.matrix_co[row][col];
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    uint8_t layerNum = get_highest_layer(layer_state);
    if (layerNum == 0) {
        rgb_matrix_set_color_all(0, 0, 0);
        return;
    }

    // Per-key indicators
    uint8_t ledIndex = 0;
    uint8_t r, g, b;
    for (uint8_t keyIndex = 0; keyIndex < 42; keyIndex++) { // 0 to 42
        ledIndex = ledIndexForKeymapIndex(keyIndex);

        if (ledIndex >= led_min && ledIndex <= led_max) {
            r = pgm_read_byte(&ledmap[layerNum][keyIndex][0]);
            g = pgm_read_byte(&ledmap[layerNum][keyIndex][1]);
            b = pgm_read_byte(&ledmap[layerNum][keyIndex][2]);

            if (!r && !g && !b) {
                RGB_MATRIX_INDICATOR_SET_COLOR(ledIndex, 0, 0, 0);
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(ledIndex, r, g, b);
            }
        }
    }
    /*
    // Underglow layer indicators
    uint8_t keyIndex = 36; // layer-switch key
    r = pgm_read_byte(&ledmap[layerNum][keyIndex][0]);
    g = pgm_read_byte(&ledmap[layerNum][keyIndex][1]);
    b = pgm_read_byte(&ledmap[layerNum][keyIndex][2]);
    for (uint8_t  i = 0; i < 12; i++) {
        ledIndex = (i < 6) ? i : i + 21;
        RGB_MATRIX_INDICATOR_SET_COLOR(ledIndex, r, g, b);
    }
    */
}

// ====================================================
// Callum One-Shot Modifiers
// ====================================================

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case BSPC_CURSOR:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case BSPC_CURSOR:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
    case OS_HYPR:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
oneshot_state os_hypr_state = os_up_unqueued;

bool app_switch_frwd_active = false;


// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    switch (keycode) {
    case PW:
        if (record->event.pressed) {
            // when keycode PW is pressed
            SEND_STRING("!Appeasing");
        } else {
            // when keycode PW is released
        }
        break;
    }
    
    
    update_swapper(
        &app_switch_frwd_active, KC_LGUI, KC_TAB, APP_SWITCH_FRWD,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );
    update_oneshot(
        &os_hypr_state, KC_HYPR, OS_HYPR,
        keycode, record
    );

    //return true;

    
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _CURSOR, _MOUSE, _SYSTEM);
}

