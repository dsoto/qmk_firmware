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

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum {
    TD_LS = 0
};

void jump_layer(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
        /* register_code(KC_LCTL); */
        /* break; */
      case 1:
      layer_off(_NAV);
      layer_off(_SYMBOL);
      layer_on(_QWERTY);
      break;
  case 2:
      // jump to symbol
      layer_off(_NAV);
      layer_on(_SYMBOL);
      break;
  case 3:
  /* case 4: */
      // jump to nav
      layer_on(_NAV);
      break;
  }
};

// use TD(TD_LS) in keymaps

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LS] = ACTION_TAP_DANCE_FN (jump_layer)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
DVORAK layer
-------------------------------------------------------------------------------------------------
|   "   |   ,   |   .   |   P   |   Y   |  TAB  |   /   |   F   |   G   |   C   |   R   |   L   |
-------------------------------------------------------------------------------------------------
|   A   |   O   |   E   |   U   |   I   |   `   |   -   |   D   |   H   |   T   |   N   |   S   |
-------------------------------------------------------------------------------------------------
|;/shift|   Q   |   J   |   K   |   X   | =/alt |  alt  |   B   |   M   |   W   |   V   |Z/shift|
-------------------------------------------------------------------------------------------------
|  ESC  |   [   |  DOWN |   UP  |  BACK | Layer |ENT/GUI| Space |  Left | Right |   ]   |   \   |
-------------------------------------------------------------------------------------------------

SYMBOL layer
-------------------------------------------------------------------------------------------------
|   1   |   2   |   3   |   4   |   5   |   `   |       |   6   |   7   |   8   |   9   |   0   |
-------------------------------------------------------------------------------------------------
|       |       |   [   |   ]   |       |       |       |       |       |       |       |       |
-------------------------------------------------------------------------------------------------
| Shift |       |       |       |   \   |       |       |       |       |       |       | Shift |
-------------------------------------------------------------------------------------------------
|       |       |       |       |       |       |       |       |       |       |       |       |
-------------------------------------------------------------------------------------------------

NAV layer
-------------------------------------------------------------------------------------------------
|       |       |       |       |       |       |       |       |       |       |       |       |
-------------------------------------------------------------------------------------------------
|       |       |       |       |       |       |       |       |       |       |       |       |
-------------------------------------------------------------------------------------------------
| Shift |       |       |KC_MS_D|KC_MS_U|       |       |       |       |       |       | Shift |
-------------------------------------------------------------------------------------------------
|       |       |       |       |       |       |       |       |       |       |       |       |
-------------------------------------------------------------------------------------------------
*/

[_QWERTY] = {
  {KC_QUOT        , KC_COMM , KC_DOT  , KC_P  , KC_Y           , KC_TAB        , KC_SLSH       , KC_F          , KC_G    , KC_C    , KC_R    , KC_L         } ,
  {KC_A           , KC_O    , KC_E    , KC_U  , KC_I           , TD(TD_LS)     , KC_MINS       , KC_D          , KC_H    , KC_T    , KC_N    , KC_S         } ,
  {SFT_T(KC_SCLN) , KC_Q    , KC_J    , KC_K  , KC_X           , ALT_T(KC_GRV) , ALT_T(KC_EQL) , KC_B          , KC_M    , KC_W    , KC_V    , SFT_T(KC_Z)  } ,
  {MO(_SYMBOL)    , KC_LBRC , KC_DOWN , KC_UP , GUI_T(KC_BSPC) , CTL_T(KC_ESC) , CTL_T(KC_ENT) , GUI_T(KC_SPC) , KC_LEFT , KC_RGHT , KC_RBRC , LT(_SYMBOL     , KC_BSLS)}
 } ,
[_SYMBOL] = {
  {KC_1           , KC_2    , KC_3    , KC_4    , KC_5           , KC_GRV    , KC_EQL        , KC_6          , KC_7    , KC_8    , KC_9    , KC_0         } ,
  {KC_NO          , KC_NO   , KC_LBRC , KC_RBRC , KC_NO          , _______   , KC_NO         , KC_NO         , KC_NO   , KC_NO   , KC_NO   , KC_NO        } ,
  {KC_LSFT        , KC_NO   , KC_NO   , KC_NO   , KC_BSLS        , _______   , _______       , KC_NO         , KC_NO   , KC_NO   , KC_NO   , KC_RSFT      } ,
  {_______        , KC_NO   , _______ , _______ , _______        , _______   , _______       , _______       , _______ , _______ , KC_NO   , KC_NO        } ,
 } ,
[_NAV] = {
  {KC_NO   , KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_POWER          } ,
  {KC_NO   , KC_NO , KC_NO   , KC_NO   , KC_NO   , _______ , _______ , KC_NO   , KC_MPRV , KC_MPLY , KC_MNXT , KC_NO          }    ,
  {KC_NO   , KC_NO , KC_BTN2 , KC_BTN1 , KC_NO   , _______ , _______ , KC_NO   , KC_VOLU , KC_MUTE , KC_VOLD , KC_NO        }    ,
  {KC_NO   , KC_NO , KC_MS_D , KC_MS_U , _______ , _______ , _______ , _______ , KC_MS_L , KC_MS_R , KC_NO   , KC_NO          }    ,
 }
};

#ifdef AUDIO_ENABLE
float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

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
