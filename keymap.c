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
#define DEBUG_ENABLE
#define CHEVR KC_NONUS_BACKSLASH
enum layer_names {
  _MAC,
  _WIN
};


enum custom_keycodes {
  BTTN = SAFE_RANGE,
  FR,
  CUST1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAC] = LAYOUT_all(
                KC_GRAVE,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_ESC,
    TG(_WIN),   KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, CUST1,
    KC_NO,      KC_CAPS,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_0,
    KC_0,       KC_LSFT,  CHEVR,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,       KC_UP,      FR,
    KC_0,       KC_LCTL,  KC_LALT, KC_LGUI,                   KC_SPC,                             KC_LGUI, KC_RALT, KC_RCTL, KC_LEFT,      KC_DOWN,     KC_RGHT
  ),
  [_WIN] = LAYOUT_all(
                KC_GRAVE,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_ESC,
    KC_TRNS,    KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, CUST1,
    KC_NO,      KC_CAPS,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_0,
    KC_0,       KC_LSFT,  CHEVR,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,       KC_UP,      FR,
    KC_0,       KC_RCTL,  KC_LALT, KC_LCTL,                   KC_SPC,                             KC_LCTL, KC_RALT, KC_RCTL, KC_LEFT,      KC_DOWN,     KC_RGHT
  )
};

keyrecord_t *r=NULL;

void tap(uint16_t keycode){if (r->event.pressed) {register_code(keycode);wait_ms(10);unregister_code(keycode);}}
bool is_shifted(void){
    if (get_mods() & MOD_BIT(KC_LSFT)){return 1;}
    return 0;
}
void shift(void){if (r->event.pressed) {register_code(KC_LSFT);wait_ms(10);}}
void unshift(void){if (r->event.pressed) {unregister_code(KC_LSFT);wait_ms(10);}}
void alt(void){if (r->event.pressed) {register_code(KC_RALT);wait_ms(10);}}
void unalt(void){if (r->event.pressed) {unregister_code(KC_RALT);wait_ms(10);}}



bool vsc_switch_view(uint16_t keycode){
    if((r->event.pressed) && (keycode == CUST1)){
      if(layer_state_is(_WIN)){
        register_code(KC_LCTL);wait_ms(10);tap(KC_J);wait_ms(10);unregister_code(KC_LCTL);
        return true;
      }
      else{
        register_code(KC_LGUI);wait_ms(10);tap(KC_J);wait_ms(10);unregister_code(KC_LGUI);
        return true;
      }
  }
  return false;
}

bool process_record_user_mac(uint16_t keycode,keyrecord_t *record){
  r=record;
  print("--- mac\n");
  switch (keycode) {
    case TG(_WIN):
      if (record->event.pressed) {
        set_bitc_LED(2);wait_ms(100);set_bitc_LED(0);
        wait_ms(200);
        set_bitc_LED(2);wait_ms(100);set_bitc_LED(0);
      }
      return true;

    case KC_1:
    case KC_2:
    case KC_3:
    case KC_4:
    case KC_5:
    case KC_6:
    case KC_7:
    case KC_8:
    case KC_9:
    case KC_0:
      if (record->event.pressed) {
        if(is_shifted()){unshift();tap(keycode);shift();}
        else{shift();tap(keycode);unshift();}
        return false;
      }
  }
  return true;
}

bool fr=false;
bool process_record_user_win(uint16_t keycode,keyrecord_t *record){
  print("--- win");
  switch (keycode) {
    case TG(_WIN):
      if (record->event.pressed) {
        set_bitc_LED(2);wait_ms(100);set_bitc_LED(0);
      }
      return true;


    case KC_Z:
      tap(KC_W); return false;
    case KC_Q:
      tap(KC_A); return false;
    case KC_A:
      if(fr){tap(KC_0); return false;}
      tap(KC_Q); return false;
    case KC_W:
      tap(KC_Z); return false;
    case KC_M:
      tap(KC_SCLN); return false;

    case KC_E:
      if(fr){tap(KC_2); return false;}
      return true;
    case KC_C:
      if(fr){tap(KC_9); return false;}
      return true;

    case KC_GRAVE:
      if(is_shifted()){unshift();alt();tap(KC_2);unalt();shift();return false;} // ~
      alt();tap(KC_7);unalt();
      return false;

    case KC_1: // !
      if(is_shifted()){tap(KC_1);return false;}
      tap(KC_SLSH);
      return false;

    case KC_2: // @
      if(is_shifted()){tap(KC_2);return false;}
      alt();tap(KC_0);unalt();
      return false;

    case KC_3: // #
      if(is_shifted()){tap(KC_3);return false;}
      alt();tap(KC_3);unalt();
      return false;

    case KC_4: // $
      if(is_shifted()){tap(KC_4);return false;}
      tap(KC_RBRC);
      return false;

    case KC_5: // %
      if(is_shifted()){tap(KC_5);return false;}
      shift();tap(KC_QUOT);unshift();
      return false;

    case KC_6: // ^
      if(is_shifted()){tap(KC_6);return false;}
      tap(KC_LBRC);
      return false;

    case KC_7: // &
      if(is_shifted()){tap(KC_7);return false;}
      tap(KC_1);
      return false;

    case KC_8: // *
      if(is_shifted()){tap(KC_8);return false;}
      tap(KC_BSLS);
      return false;

    case KC_9: // (
      if(is_shifted()){tap(KC_9);return false;}
      tap(KC_5);
      return false;

    case KC_0: // )
      if(is_shifted()){tap(KC_0);return false;}
      tap(KC_MINS);
      return false;

    case KC_MINS:
      if(is_shifted()){unshift();tap(KC_8);shift();return false;}
      tap(KC_6);
      return false;

    case KC_LBRC:
      if(is_shifted()){unshift();alt();tap(KC_4);unalt();shift();return false;}
      alt();tap(KC_5);unalt();
      return false;
    case KC_RBRC:
      if(is_shifted()){unshift();alt();tap(KC_EQL);unalt();shift();return false;}
      alt();tap(KC_MINS);unalt();
      return false;
    case KC_BSLS:
      if(is_shifted()){unshift();alt();tap(KC_6);unalt();shift();return false;}
      alt();tap(KC_8);unalt();
      return false;

    case KC_SCLN:
      if(is_shifted()){unshift();tap(KC_DOT);shift();return false;}
      tap(KC_COMM);
      return false;

    case KC_QUOT:
      if(is_shifted()){unshift();tap(KC_3);shift();return false;}
      tap(KC_4);
      return false;

    case KC_COMM:
      if(is_shifted()){unshift();tap(100);shift();return false;}
      tap(KC_M);
      return false;

    case KC_DOT:
      if(is_shifted()){tap(100);return false;}
      shift();tap(KC_COMM);unshift();
      return false;

    case KC_SLSH:
      if(is_shifted()){tap(KC_M);return false;}
      shift();tap(KC_DOT);unshift();
      return false;

  }
  return true;
}

void get_fr(uint16_t keycode,keyrecord_t *record){
 if (keycode == FR){
    if (record->event.pressed) {fr=true;}
    else{fr=false;}
 }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(vsc_switch_view(keycode)){return false;}
  set_single_persistent_default_layer(_MAC);
  get_fr(keycode,record);
  if(layer_state_is(_WIN)){return process_record_user_win(keycode,record);}
  else{return process_record_user_mac(keycode,record);}
  return true;
}



void keyboard_post_init_user(void) {debug_matrix = true;}
void matrix_init_user(void) {layer_off(_WIN);matrix_init_remote_kb();}
void matrix_scan_user(void) {matrix_scan_remote_kb();}

bool encoder_update_user(uint8_t index, bool clockwise) {return false;}