#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    OSG_STATE_DISABLED = 1,
    OSG_STATE_MODS_DOWN,
    OSG_STATE_MODS_UP,
    OSG_STATE_MODS_APPLIED,
} oneshot_group_state;

typedef uint16_t (*oneshot_group_get_mod_for_key_t)(uint16_t);
typedef bool (*oneshot_group_is_cancel_key_t)(uint16_t);
typedef bool (*oneshot_group_is_ignord_key_t)(uint16_t);

typedef struct {
    oneshot_group_state             state;
    uint8_t                         layer;
    oneshot_group_get_mod_for_key_t get_mod_for_key;
    oneshot_group_is_ignord_key_t   is_ignored_key;
    oneshot_group_is_cancel_key_t   is_cancel_key;
    deferred_token                  oneshot_cancel_token;
} oneshot_group_mod_config;

void update_oneshot_group(oneshot_group_mod_config *config, uint16_t keycode, keyrecord_t *record);
