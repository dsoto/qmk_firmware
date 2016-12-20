#include "kinesis_stapelberg.h"

#define _DVORAK 0 // Base Dvorak layer
#define _MEDIA 1  // Media layer
#define _SYMBOL 2 // Numpad and Symbol layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DVORAK] = KEYMAP(
        // left hand
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5, KC_F6, KC_F7, KC_F8,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,
        KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,
        KC_BSPC,  KC_A,    KC_O,    KC_E,    KC_U,   KC_I,
        KC_LSFT,  KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,
                  KC_ESC,  KC_LBRC, KC_DOWN, KC_UP,
        // left thumb
                            KC_LGUI, KC_LCTL,
                                     KC_LALT,
                   /* KC_BSPC, KC_DEL,  TG(_MEDIA), */
                   KC_BSPC, TO(_SYMBOL),  TO(_MEDIA),
        // right hand
        KC_F9,  KC_F10,   KC_F11,   KC_F12,   KC_PSCR, KC_SLCK, KC_PAUS, KC_FN0, KC_1,
        KC_6,   KC_7,     KC_8,     KC_9,     KC_0,    KC_EQL,
        KC_F,   KC_G,     KC_C,     KC_R,     KC_L,    KC_SLSH,
        KC_D,   KC_H,     KC_T,     KC_N,     KC_S,    KC_MINS,
        KC_B,   KC_M,     KC_W,     KC_V,     KC_Z,    KC_RSFT,
                          KC_LEFT,  KC_RIGHT, KC_RBRC, KC_BSLS,
        // right thumb
        KC_RCTL,    KC_RGUI,
        KC_RALT,
        /* TG(_MEDIA), KC_ENT, KC_SPC */
        TO(_MEDIA), KC_ENT, KC_SPC
    ),

[_MEDIA] = KEYMAP(
       // left hand
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                KC_NO,   KC_NO,   KC_MS_D, KC_MS_U,
        // left thumb
                                           KC_NO,   KC_NO,
                                                    KC_NO,
                                  /* KC_NO,   KC_NO,   KC_TRNS, */
                                  KC_NO,   TO(_DVORAK),   TO(_SYMBOL),
       // right hand
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_POWER,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
       KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,
       KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,
                KC_MS_L, KC_MS_R, KC_NO,   KC_NO,
       // right thumb
       KC_NO, KC_NO,
       KC_NO,
       /* KC_TRNS, KC_ENT, KC_NO */
       TO(_SYMBOL), KC_ENT, KC_NO
),

// this will eventually be a symbol layer with parenthesis and numbers
[_SYMBOL] = KEYMAP(
       // left hand
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_LPRN, KC_RPRN, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_LCBR, KC_RCBR, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                KC_NO,   KC_NO,   KC_NO,   KC_NO,
        // left thumb
                                           KC_NO,   KC_NO,
                                                    KC_NO,
                                  KC_NO,   TO(_MEDIA),   TO(_DVORAK),
       // right hand
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_7,    KC_8,    KC_9,   KC_NO,   KC_NO,
       KC_NO,   KC_4,    KC_5,    KC_6,   KC_NO,   KC_NO,
       KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,
                KC_NO,   KC_0,   KC_NO,   KC_NO,
       // right thumb
       KC_NO, KC_NO,
       KC_NO,
       TO(_DVORAK), KC_NO, KC_NO
)
};


const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
