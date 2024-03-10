#include "oneshot.h"
#include <stdint.h>
#include "debug.h"
#include "timer.h"


#define ONESHOT_ACTIVE_TIMEOUT 500
#define ONESHOT_UNUSED_TIMEOUT 300

void update_oneshot(
    oneshot_key_t* oskey,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (oskey->oneshot_state == os_up_unqueued) {
                register_code(mod);
            }
            oskey->oneshot_state = os_down_unused;
            oskey->down_unused_time = timer_read();
            dprintf("trigger down (on?), mod: %d, ? -> os_down_unused\n", mod);
        } else {
            // Trigger keyup
            switch (oskey->oneshot_state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                oskey->oneshot_state = os_up_queued;
                oskey->queued_time = timer_read();
                dprintf("trigger up, mod: %d, os_down_unused -> os_up_queued\n", mod);
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                oskey->oneshot_state = os_up_unqueued;
                unregister_code(mod);
                dprintf("trigger up (off), mod: %d, os_down_used -> os_up_unqueued\n", mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && 
                (oskey->oneshot_state == os_up_queued || oskey->oneshot_state == os_up_queued_used)) {
                // Cancel oneshot on designated cancel keydown.
                oskey->oneshot_state = os_up_unqueued;
                unregister_code(mod);
                dprintf("cancel (off), mod: %d, ? -> os_up_unqueued\n", mod);
            }
            if (!is_oneshot_ignored_key(keycode)) {
                switch (oskey->oneshot_state) {
                case os_down_unused:
                    oskey->oneshot_state = os_down_used;
                    dprintf("key down, mod: %d, os_down_unused -> os_down_used\n", mod);
                    break;
                case os_up_queued:
                    oskey->oneshot_state = os_up_queued_used;
                    dprintf("key down, mod: %d, os_up_queued -> os_up_queued_used\n", mod);
                    break;
                case os_up_queued_used:
                    oskey->oneshot_state = os_up_unqueued;
                    unregister_code(mod);
                    dprintf("key down (off), mod: %d, os_up_queued_used -> os_up_unqueued\n", mod);
                    break;
                default:
                    break;
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (oskey->oneshot_state) {
                // case os_down_unused:
                //     oskey->oneshot_state = os_down_used;
                //     dprintf("key up, mod: %d, os_down_unused -> os_down_used\n", mod);
                //     break;
                // case os_up_queued:
                //     oskey->oneshot_state = os_up_unqueued;
                //     unregister_code(mod);
                //     dprintf("key up (off), mod: %d, os_up_queued -> os_up_unqueued\n", mod);
                //     break;
                case os_up_queued_used:
                    oskey->oneshot_state = os_up_unqueued;
                    unregister_code(mod);
                    dprintf("key up (off), mod: %d, os_up_queued_used -> os_up_unqueued\n", mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void scan_oneshot(
    oneshot_key_t* oskey,
    uint16_t mod,
    uint16_t trigger)
{
    switch(oskey->oneshot_state){
    case os_up_queued:
    {
        uint16_t elapsed = timer_elapsed(oskey->queued_time);
        if (elapsed >= ONESHOT_ACTIVE_TIMEOUT)
        {
            oskey->oneshot_state = os_up_unqueued;
            oskey->queued_time = 0;
            unregister_code(mod);
            dprintf("timeout, mod: %d, os_up_queued -> os_up_unqueued\n", mod);
        }
        break;
    }
    case os_down_unused:
    {
        uint16_t elapsed = timer_elapsed(oskey->down_unused_time);
        if (elapsed >= ONESHOT_UNUSED_TIMEOUT)
        {
            oskey->oneshot_state = os_down_used;
            oskey->down_unused_time = 0;
            dprintf("timeout, mod: %d, os_down_unused -> os_down_used\n", mod);
        }
        break;
    }
    default:
        break;
    }
}


bool update_oneshot_layer(
    oneshot_key_t* oskey,
    uint8_t layer,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {

    // //get current layer
    // uint8_t key_layer = read_source_layers_cache(record->event.key);
    // //get keycode on that layer
    // uint16_t kkl =  keymap_key_to_keycode(key_layer, record->event.key);
    // //get keycode on 0 layer. we can use that to find original keycode on key up
    // uint16_t kk0 = keymap_key_to_keycode(0, record->event.key);
    bool layerChanged = false;
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (oskey->oneshot_state == os_up_unqueued) {
                layer_on(layer);
                layerChanged = true;
            }
            oskey->oneshot_state = os_down_unused;
            oskey->down_unused_time = timer_read();
            dprintf("LAYER: trigger down, layer: %d, ? -> os_down_unused\n", layer);
        } else {
            // Trigger keyup
            switch (oskey->oneshot_state) {
            case os_down_unused:
                // If we didn't use the layer while trigger was held, queue it.
                oskey->oneshot_state = os_up_queued;
                oskey->queued_time = timer_read();
                dprintf("LAYER: trigger up, layer: %d, os_down_unused -> os_up_queued\n", layer);
                break;
            case os_down_used:
                // If we did use the layer while trigger was held, unregister it.
                oskey->oneshot_state = os_up_unqueued;
                layer_off(layer);
                layerChanged = true;
                dprintf("LAYER: trigger up (off), layer: %d, os_down_used -> os_up_unqueued\n", layer);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode) && 
                (oskey->oneshot_state == os_up_queued || oskey->oneshot_state == os_up_queued_used)) {
                // Cancel oneshot on designated cancel keydown.
                oskey->oneshot_state = os_up_unqueued;
                layer_off(layer);
                layerChanged = true;
                dprintf("LAYER: cancel (off), layer: %d, ? -> os_up_unqueued\n", layer);
            }
            if (!is_oneshot_layer_ignored_key(keycode)) {
                switch (oskey->oneshot_state) {
                case os_down_unused:
                    oskey->oneshot_state = os_down_used;
                    dprintf("LAYER: key down, layer: %d, os_down_unused -> os_down_used\n", layer);
                    break;
                case os_up_queued:
                    oskey->oneshot_state = os_up_queued_used;
                    dprintf("LAYER: key down, layer: %d, os_up_queued -> os_up_queued_used\n", layer);
                    break;
                case os_up_queued_used:
                    oskey->oneshot_state = os_up_unqueued;
                    layer_off(layer);
                    layerChanged = true;
                    dprintf("LAYER: key down (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    break;
                default:
                    break;
                }
            }
        } else {
            if (!is_oneshot_layer_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (oskey->oneshot_state) {
                // case os_down_unused:
                //     oskey->oneshot_state = os_down_used;
                //     dprintf("LAYER: key up, layer: %d, os_down_unused -> os_down_used\n", layer);
                //     break;
                // case os_up_queued:
                //     oskey->oneshot_state = os_up_unqueued;
                //     layer_off(layer);
                //     dprintf("LAYER: key up (off), layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                //     break;
                case os_up_queued_used:
                    oskey->oneshot_state = os_up_unqueued;
                    layer_off(layer);
                    layerChanged = true;
                    dprintf("LAYER: key up (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    break;
                default:
                    break;
                }
            }
        }
    }
    return layerChanged;
}

void scan_oneshot_layer(
    oneshot_key_t* oskey,
    uint8_t layer,
    uint16_t trigger)
{
    switch(oskey->oneshot_state){
    case os_up_queued:
    {
        uint16_t elapsed = timer_elapsed(oskey->queued_time);
        if (elapsed >= ONESHOT_ACTIVE_TIMEOUT)
        {
            oskey->oneshot_state = os_up_unqueued;
            oskey->queued_time = 0;
            layer_off(layer);
            dprintf("LAYER: timeout, layer: %d, os_up_queued -> os_up_unqueued\n", layer);
        }
        break;
    }
    case os_down_unused:
    {
        uint16_t elapsed = timer_elapsed(oskey->down_unused_time);
        if (elapsed >= ONESHOT_UNUSED_TIMEOUT)
        {
            oskey->oneshot_state = os_down_used;
            oskey->down_unused_time = 0;
            dprintf("LAYER: timeout, layer: %d, os_down_unused -> os_down_used\n", layer);
        }
        break;
    }
    default:
        break;
    }
}
