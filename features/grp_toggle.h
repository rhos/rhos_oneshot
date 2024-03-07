#pragma once

#include QMK_KEYBOARD_H

void send_extra_grp_toggle(void) {
  uint8_t mods = get_mods();
  unregister_mods(mods);

  register_code(KC_LGUI);
  tap_code(KC_SPC);
  unregister_code(KC_LGUI);
  
  register_mods(mods);
}

static uint8_t in_extra_layer = 0;
static uint8_t extra_grp_toggled = 0;

void extra_grp_on(void) {
  if(extra_grp_toggled)
    return;
  extra_grp_toggled = 1;
  send_extra_grp_toggle();
}
void extra_grp_off(void) {
  if(!extra_grp_toggled)
    return;
  extra_grp_toggled = 0;
  send_extra_grp_toggle();
}

layer_state_t update_default_extra_grp(layer_state_t state, uint8_t layer){
  if (get_highest_layer(state) == layer) {
    if (!in_extra_layer) {
      in_extra_layer = 1;
      extra_grp_on();
    }
  }
  else {
    if(in_extra_layer) {
      in_extra_layer = 0;
      extra_grp_off();
    }
  }
  return state;
}

layer_state_t update_extra_grp(layer_state_t state) {
  if(in_extra_layer) {
    if (state == 0) { //is base layer
      extra_grp_on();
    }
    else {
      extra_grp_off();
    }
  }
  return state;
}
