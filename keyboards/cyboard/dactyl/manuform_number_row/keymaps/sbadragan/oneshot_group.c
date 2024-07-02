#include "oneshot_group.h"

uint32_t cancel_oneshot_group(uint32_t trigger_time, void *cb_arg) {
    oneshot_group_mod_config *config = (oneshot_group_mod_config *)cb_arg;
    config->state                    = OSG_STATE_DISABLED;
    clear_mods();
    layer_off(config->layer);
    return 0;
}

void update_oneshot_group(oneshot_group_mod_config *config, uint16_t keycode, keyrecord_t *record) {
    uint16_t mod          = (*(config->get_mod_for_key))(keycode);
    bool     isMod        = mod != 0;
    bool     isKeyDown    = record->event.pressed;
    bool     isIgnoredKey = (*(config->is_ignored_key))(keycode);
    bool     isCancelKey  = (*(config->is_ignored_key))(keycode);

#ifdef CONSOLE_ENABLE
    uprintf("called update oneshot: state: %d, key: 0x%04X, pressed: %u, mod: %d, isMod %d, ignored: %d, canceled: %d\n", config->state, keycode, record->event.pressed, mod, isMod, isIgnoredKey, isCancelKey);
#endif
    if (!isMod && isIgnoredKey) {
        return;
    }

    if (isCancelKey) {
        config->state = OSG_STATE_DISABLED;
        clear_mods();
        layer_off(config->layer);
    }

    // transition to next state based on input
    switch (config->state) {
        case OSG_STATE_DISABLED:
            if (isMod && isKeyDown) {
                config->state = OSG_STATE_MODS_DOWN;
                register_mods(MOD_BIT(mod));
                layer_clear();
                layer_on(config->layer);
            }
            return;
        case OSG_STATE_MODS_DOWN:
            if (isMod) {
                if (isKeyDown) {
                    register_mods(MOD_BIT(mod));
                } else {
                    // is this the last mod being released?
                    if (get_mods() == MOD_BIT(mod)) {
                        config->state                = OSG_STATE_MODS_UP;
                        config->oneshot_cancel_token = defer_exec(ONESHOT_TIMEOUT, cancel_oneshot_group, config);
                    }
                }
            } else {
                if (isKeyDown) {
                    config->state = OSG_STATE_MODS_APPLIED;
                    layer_off(config->layer);
                }
            }
            return;
        case OSG_STATE_MODS_UP:
            if (isKeyDown) {
                cancel_deferred_exec(config->oneshot_cancel_token);
                if (isMod) {
                    clear_mods();
                    register_mods(MOD_BIT(mod));
                    layer_clear();
                    layer_on(config->layer);
                    config->state = OSG_STATE_MODS_DOWN;
                } else {
                    layer_off(config->layer);
                    config->state = OSG_STATE_MODS_APPLIED;
                }
            }
            return;
        case OSG_STATE_MODS_APPLIED:
            if (isKeyDown) {
                clear_mods();
                if (isMod) {
                    register_mods(MOD_BIT(mod));
                    layer_clear();
                    layer_on(config->layer);
                    config->state = OSG_STATE_MODS_DOWN;

                } else {
                    layer_off(config->layer);
                    config->state = OSG_STATE_DISABLED;
                }
            }
            return;
    }
}
