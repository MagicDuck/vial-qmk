#include "oneshot.h"

void cancelMod(oneshot_mod_state *mod_state) {
    unregister_mods(MOD_BIT(mod_state->mod));
#ifdef CONSOLE_ENABLE
    /* uprintf("canceled mod: %u\n", get_mods()); */
#endif
}
void activateMod(oneshot_mod_state *mod_state) {
    register_mods(MOD_BIT(mod_state->mod));
#ifdef CONSOLE_ENABLE
    /* uprintf("activated mod %u\n", get_mods()); */
#endif
}

uint32_t cancelOneshotCb(uint32_t trigger_time, void *cb_arg) {
    oneshot_mod_state *mod_state = (oneshot_mod_state *)cb_arg;
    mod_state->state             = os_up_unqueued;
    on_before_oneshot_deferred_mod_cancel(mod_state);
    cancelMod(mod_state);
    return 0;
}

void update_oneshot(oneshot_mod_state *mod_state, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    oneshot_state *state = &(mod_state->state);

    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                *state = os_down_unused;
                on_before_oneshot_mod_activate(mod_state, keycode, record);
                activateMod(mod_state);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = os_up_queued;
                    defer_exec(ONESHOT_TIMEOUT, cancelOneshotCb, mod_state);
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = os_up_unqueued;
                    cancelMod(mod_state);
                    break;
                default:
                    break;
            }
        }
    } else {
#ifdef CONSOLE_ENABLE
        /* uprintf("stephan: oneshot: key event, key: 0x%04X, pressed: %u, mod_state: %d, mods: %u\n", keycode, record->event.pressed, (int)*state, get_mods()); */
#endif
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                on_before_oneshot_mod_cancel(mod_state, keycode, record);
                cancelMod(mod_state);
                return;
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        on_before_oneshot_mod_cancel(mod_state, keycode, record);
                        break;
                    case os_up_queued:
                        *state = os_up_unqueued;
                        on_before_oneshot_mod_cancel(mod_state, keycode, record);
                        cancelMod(mod_state);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
