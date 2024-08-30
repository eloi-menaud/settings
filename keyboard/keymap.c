/* Copyright 2021 Jay Greco
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
#include "./data.h"
#define DEBUG_ENABLE
#define CHEVR KC_NONUS_BACKSLASH



Transform transforms[] = {

	{{KC_Q, 0, 0, 0},{KC_A, 0, 0, 0}},       // a
	{{KC_Q, 1, 0, 0},{KC_A, 1, 0, 0}},       // A
	{{KC_Q, 0, 0, 1},{KC_0, 0, 0, 0}},       // à

	{{KC_A, 0, 0, 0},{KC_Q, 0, 0, 0}},       // q
	{{KC_A, 1, 0, 0},{KC_Q, 1, 0, 0}},       // Q

	{{KC_W, 0, 0, 0},{KC_Z, 0, 0, 0}},       // w
	{{KC_W, 1, 0, 0},{KC_Z, 1, 0, 0}},       // W

	{{KC_Z, 0, 0, 0},{KC_W, 0, 0, 0}},       // z
	{{KC_Z, 1, 0, 0},{KC_W, 1, 0, 0}},       // Z

	{{KC_M, 0, 0, 0},{KC_SCLN, 0, 0, 0}},    // m
	{{KC_M, 1, 0, 0},{KC_SCLN, 1, 0, 0}},    // M

	{{KC_E, 0, 0, 1},{KC_2, 0, 0, 0}},       // é
	{{KC_E, 1, 0, 1},{KC_7, 0, 0, 0}},       // è

	{{KC_C, 0, 0, 1},{KC_9, 0, 0, 0}},       // ç

	{{KC_GRAVE, 0, 0, 0},{KC_7, 0, 1, 0}},   // `
	{{KC_1, 0, 0, 0},{KC_2, 0, 1, 0}},       // ~

	{{KC_1, 0, 0, 0},{KC_SLSH, 0, 0, 0}},    // !
	{{KC_2, 0, 0, 0},{KC_0, 0, 1, 0}},       // @
	{{KC_3, 0, 0, 0},{KC_3, 0, 1, 0}},       // #
	{{KC_4, 0, 0, 0},{KC_RBRC, 0, 0, 0}},    // $
	{{KC_5, 0, 0, 0},{KC_QUOT, 1, 0, 0}},    // %
	{{KC_6, 0, 0, 0},{KC_LBRC, 0, 0, 0}},    // ^
	{{KC_7, 0, 0, 0},{KC_1, 0, 0, 0}},       // &
	{{KC_8, 0, 0, 0},{KC_BSLS, 0, 0, 0}},    // *
	{{KC_9, 0, 0, 0},{KC_5, 0, 0, 0}},       // (
	{{KC_0, 0, 0, 0},{KC_MINS, 0, 0, 0}},    // )

	{{KC_MINS, 0, 0, 0},{KC_6, 0, 0, 0}},    // -
	{{KC_MINS, 1, 0, 0},{KC_8, 0, 0, 0}},    // _

	{{KC_LBRC, 0, 0, 0},{KC_5, 0, 1, 0}},    // [
	{{KC_LBRC, 1, 0, 0},{KC_4, 0, 1, 0}},    // {

	{{KC_RBRC, 0, 0, 0},{KC_MINS, 0, 1, 0}}, // ]
	{{KC_RBRC, 1, 0, 0},{KC_EQL, 0, 1, 0}},  // }

	{{KC_BSLS, 0, 0, 0},{KC_8, 0, 1, 0}},    // back /
	{{KC_BSLS, 1, 0, 0},{KC_6, 0, 1, 0}},    // |

	{{KC_SCLN, 0, 0, 0},{KC_COMM, 0, 0, 0}}, // ;
	{{KC_SCLN, 1, 0, 0},{KC_DOT, 0, 0, 0}},  // :

	{{KC_QUOT, 0, 0, 0},{KC_4, 0, 0, 0}},    // '
	{{KC_QUOT, 1, 0, 0},{KC_3, 0, 0, 0}},    // "

	{{KC_COMM, 0, 0, 0},{KC_M, 0, 0, 0}},    // ,
	{{KC_COMM, 1, 0, 0},{100, 0, 0, 0}},     // <

	{{KC_DOT, 0, 0, 0},{KC_COMM, 1, 0, 0}},  // .
	{{KC_DOT, 1, 0, 0},{100, 1, 0, 0}},      // >

	{{KC_SLSH, 0, 0, 0},{KC_DOT, 1, 0, 0}},  // /
	{{KC_SLSH, 1, 0, 0},{KC_M, 1, 0, 0}},    // ?


};
const int nb_transforms = sizeof(transforms) / sizeof(transforms[0]);

bool parse(KeyData typed, Transform tr){
	if(
		typed.keycode != tr.input.keycode ||
		typed.alt     != tr.input.alt     ||
		typed.shift   != tr.input.shift   ||
		typed.special != tr.input.special
	){return false;}

	if(tr.output.shift)
	{register_code(KC_LSFT);}
	else
	{unregister_code(KC_LSFT);}
	wait_ms(10);

	if(tr.output.alt)
	{register_code(KC_RALT);}
	else
	{unregister_code(KC_RALT);}
	wait_ms(10);

	register_code(tr.output.keycode);
	wait_ms(10);
	unregister_code(tr.output.keycode);

	if(tr.input.shift)
	{register_code(KC_LSFT);}
	else
	{unregister_code(KC_LSFT);}
	wait_ms(10);

	if(tr.input.alt)
	{register_code(KC_RALT);}
	else
	{unregister_code(KC_RALT);}
	wait_ms(10);

	return true;
}

enum custom_keycodes {
	BTTN = SAFE_RANGE,
	SPECIAL,
	BROWSER,
	CODE,
	TERM,
	WINDOW
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
                KC_GRAVE,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_ESC,
    BTTN,       KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
    BROWSER,      KC_CAPS,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,        WINDOW,
    CODE,       KC_LSFT,  CHEVR,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,       KC_UP,     SPECIAL,
    TERM,       KC_RCTL,  KC_LALT, KC_LCTL,                   KC_SPC,                             KC_LCTL, KC_RALT, KC_RCTL, KC_LEFT,      KC_DOWN,    KC_RGHT
  )
};




bool special=false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	if (keycode == SPECIAL){
		special = (record->event.pressed);
		return false;
	}


	if (keycode == BROWSER && record->event.pressed ){
		  register_code(KC_LALT);wait_ms(10);  register_code(KC_B);wait_ms(10);
		unregister_code(KC_LALT);wait_ms(10);unregister_code(KC_B);wait_ms(10);
		return false;
	}
	if (keycode == CODE && record->event.pressed ){
		  register_code(KC_LALT);wait_ms(10);  register_code(KC_C);wait_ms(10);
		unregister_code(KC_LALT);wait_ms(10);unregister_code(KC_C);wait_ms(10);
		return false;
	}
	if (keycode == TERM && record->event.pressed ){
		  register_code(KC_LALT);wait_ms(10);  register_code(KC_T);wait_ms(10);
		unregister_code(KC_LALT);wait_ms(10);unregister_code(KC_T);wait_ms(10);
		return false;
	}
	if (keycode == WINDOW && record->event.pressed ){
		  register_code(KC_F11);wait_ms(10);
		unregister_code(KC_F11);wait_ms(10);
		return false;
	}



	if(! record->event.pressed){return true;}

	KeyData typed = {
		keycode,
		get_mods() & MOD_BIT(KC_LSFT),
		get_mods() & MOD_BIT(KC_RALT),
		special
	};

	for (int i = 0; i < nb_transforms; ++i) {
        if(parse(typed, transforms[i])){
			return false;
		}
    }

  	return true;
}


void keyboard_post_init_user(void) {debug_matrix = true;}

void matrix_scan_user(void) {matrix_scan_remote_kb();}

bool encoder_update_user(uint8_t index, bool clockwise) {return false;}