#include QMK_KEYBOARD_H

#include "layout.h"
#include "features/oneshot.h"
#include "features/grp_toggle.h"

// prevent accidental boot activation

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) {
    reset_keyboard();
  }
}

void u_td_fn_grp(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) {
    send_extra_grp_toggle();
  }
}

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
    [U_TD_GRP] = ACTION_TAP_DANCE_FN(u_td_fn_grp)
};

// overrides

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);
// const key_override_t hsign_override = ko_make_with_layers(MOD_BIT(KC_ALGR), KC_M, KC_RBRC, (1 << U_EXTRA));
// const key_override_t hsign_override = ko_make_with_layers(MOD_BIT(KC_LSFT), KC_M, KC_RBRC, (1 << U_EXTRA));
// const key_override_t ee_override = ko_make_with_layers(MOD_BIT(KC_ALGR), KC_T, KC_GRV, (1 << U_EXTRA));
// const key_override_t dotcomm_override = ko_make_with_layers(MOD_BIT(KC_LSFT), KC_DOT, KC_COMM, (1 << U_BASE));
const key_override_t media_up = ko_make_basic(MOD_MASK_SHIFT, KC_VOLU, KC_MPRV);
const key_override_t media_center = ko_make_basic(MOD_MASK_SHIFT, KC_MUTE, KC_MPLY);
const key_override_t media_down = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_MNXT);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    // &hsign_override,
    // &ee_override,
    // &dotcomm_override,
    &media_up,
    &media_center,
    &media_down,
    NULL
};

// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define LAYER_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, LAYER_##LAYER),
LAYER_LIST
#undef LAYER_X
};


// oneshot rules

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    #define OSLAYER_X(OSLAYER) case OSL_##OSLAYER:
    OSLAYER_LIST
    #undef OSLAYER_X
    case OS_CNCL:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    #define OSLAYER_X(OSLAYER) case OSL_##OSLAYER:
    OSLAYER_LIST
    #undef OSLAYER_X

    #define OSMOD_X(OSMOD) case OS_##OSMOD:
    OSMOD_LIST
    #undef OSMOD_X
        return true;
    default:
        return false;
    }
} 

bool is_oneshot_layer_cancel_key(uint16_t keycode)
{
  switch (keycode) {
  #define OSLAYER_X(OSLAYER) case OSL_##OSLAYER:
  OSLAYER_LIST
  #undef OSLAYER_X
  case OS_CNCL:
    //we cancel ONLY one shot behaviour(queued buttons, hold stays), so pressing and holding osl button once always means we are on pressed layer
    return true;
  default:
    return false;
  }
}

bool is_oneshot_layer_ignored_key(uint16_t keycode)
{
  //non ignoring osl keys prevents trilayer activation without holding one of layer keys
  return false;
}

#define OSMOD_X(OSMOD) oneshot_key_t os_##OSMOD##_key = {os_up_unqueued, 0};
OSMOD_LIST
#undef OSMOD_X

#define OSLAYER_X(OSLAYER) oneshot_key_t os_##OSLAYER##_key = {os_up_unqueued, 0};
OSLAYER_LIST
#undef OSLAYER_X

// layer change

layer_state_t default_layer_state_set_user(layer_state_t state){
  dprintf("DEFLAYERSTATE: %d \n", state);
  return update_default_extra_grp(state, U_EXTRA);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  dprintf("LAYERSTATE: %d \n", state);
  state = update_extra_grp(state);
  return update_tri_layer_state(state,  U_NAV, U_NUM, U_FUN);
}

// process key presses

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    dprintf("KEYCODE: pressed %d \n", keycode);
  }
  else {
    dprintf("KEYCODE: released %d \n", keycode);
  }

  if( 
  #define OSLAYER_X(OSLAYER) update_oneshot_layer(&os_##OSLAYER##_key, U_##OSLAYER, OSL_##OSLAYER, keycode, record) |
  OSLAYER_LIST
  #undef OSLAYER_X
    false)
  {
    keycode = get_record_keycode(record, true);
    if (record->event.pressed) {
      dprintf("CORRECTED: pressed %d \n", keycode);
    }
    else {
      dprintf("CORRECTED: released %d \n", keycode);
    }
  }
  #define OSMOD_X(OSMOD) update_oneshot(&os_##OSMOD##_key, KC_##OSMOD, OS_##OSMOD, keycode, record);
  OSMOD_LIST
  #undef OSMOD_X

  return true;
};

// caps word settings

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        #define OSLAYER_X(OSLAYER) case OSL_##OSLAYER:
        OSLAYER_LIST
        #undef OSLAYER_X
        #define OSMOD_X(OSMOD) case OS_##OSMOD:
        OSMOD_LIST
        #undef OSMOD_X
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// auto shift keys

bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
  if(get_highest_layer(default_layer_state) != U_LEFT)
    return false;

  switch (keycode) {
      case KC_1 ... KC_0:
      case KC_MINUS ... KC_SLASH:
      case KC_F1 ... KC_F12:
          return true;
  }
  return false;
}

//matrix scan

void matrix_scan_user(void) {
  #define OSMOD_X(OSMOD) scan_oneshot(&os_##OSMOD##_key, KC_##OSMOD, OS_##OSMOD);
  OSMOD_LIST
  #undef OSMOD_X

  #define OSLAYER_X(OSLAYER) scan_oneshot_layer(&os_##OSLAYER##_key, U_##OSLAYER, OSL_##OSLAYER);
  OSLAYER_LIST
  #undef OSLAYER_X
}

// debug

void keyboard_post_init_user(void) {
  // debug_enable=true;
  // debug_matrix=true;
  //adebug_keyboard=true;
  //debug_mouse=true;
}