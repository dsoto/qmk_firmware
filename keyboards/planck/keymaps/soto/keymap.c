// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMBOL 1
#define _NAV 2
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _PLOVER 5
#define _ADJUST 16

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  | Ctrl | Alt  | GUI  | Bksp |  NO  | ENT  | Space| GUI  | ALT  | Ctrl |  NO  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB , KC_QUOT , KC_COMM , KC_DOT  , KC_P           , KC_Y        , KC_F   , KC_G          , KC_C    , KC_R    , KC_L  , KC_SLSH}  ,
  {KC_GRV  , KC_A    , KC_O    , KC_E    , KC_U           , KC_I        , KC_D   , KC_H          , KC_T    , KC_N    , KC_S  , KC_MINS}  ,
  {KC_LSFT , KC_SCLN , KC_Q    , KC_J    , KC_K           , KC_X        , KC_B   , KC_M          , KC_W    , KC_V    , KC_Z  , KC_RSFT } ,
  {KC_NO   , KC_ESC  , KC_LCTL , KC_LALT , GUI_T(KC_BSPC) , TO(_SYMBOL) , KC_ENT , GUI_T(KC_SPC) , KC_RALT , KC_RCTL , KC_NO , KC_NO}
},
[_SYMBOL] = {
  {KC_GRV  , KC_1  , KC_2  , KC_3    , KC_4    , KC_5     , KC_6   , KC_7   , KC_8  , KC_9  , KC_0  , KC_EQL}  ,
  {KC_NO   , KC_NO , KC_NO , KC_LBRC , KC_RBRC , KC_NO    , KC_NO  , KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO}   ,
  {KC_LSFT , KC_NO , KC_NO , KC_NO   , KC_BSLS , KC_NO    , KC_NO  , KC_NO  , KC_NO , KC_NO , KC_NO , KC_RSFT} ,
  {KC_NO   , KC_NO , KC_NO , KC_NO   , KC_BSPC , TO(_NAV) , KC_ENT , KC_SPC , KC_NO , KC_NO , KC_NO , KC_NO}   ,
},
[_NAV] = {
    {KC_NO   , KC_NO , KC_NO , KC_NO   , KC_NO , KC_NO       , KC_NO , KC_NO   , KC_NO   , KC_NO , KC_NO , KC_NO   } ,
    {KC_NO   , KC_NO , KC_NO , KC_NO   , KC_NO , KC_NO       , KC_NO , KC_NO   , KC_NO   , KC_NO , KC_NO , KC_NO   } ,
    {KC_LSFT , KC_NO , KC_NO , KC_NO   , KC_NO , KC_NO       , KC_NO , KC_NO   , KC_NO   , KC_NO , KC_NO , KC_RSFT } ,
    {KC_NO   , KC_NO , KC_NO , KC_DOWN , KC_UP , TO(_QWERTY) , KC_NO , KC_LEFT , KC_RGHT , KC_NO , KC_NO , KC_NO   } ,
}
};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
