#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "oneshot_group.h"
#include "swapper.h"
#include "repeat.h"

enum layers { BASE_LAYER, SYM_LAYER, NAV_LAYER, NUM_LAYER_LEFT, NUM_LAYER_RIGHT, NAV_MODS_LAYER, SYM_MODS_LAYER, CLR_NAV_LAYER };

enum keycodes {
    // Custom oneshot mod implementation.
    OS_LSHFT = SAFE_RANGE,
    OS_LCTRL,
    OS_LALT,
    OS_LCMD,

    OS_RSHFT,
    OS_RCTRL,
    OS_RALT,
    OS_RCMD,

    SW_WIN, // Switch to next window         (cmd-tab)
    SW_TAB, // Switch to next tab            (ctrl-tab)
    REPEAT,
    CODE_BLK,
    SN1,
    SN2,
    SN3,
    SN4,
    CLR_NAV,
    ONE_SHIFT
};

#define OSM_HYPR OSM(MOD_HYPR)
#define OS_LGUI OSM(MOD_LGUI)
// #define OS_LCTL OSM(MOD_LCTL)
// #define OS_LALT OSM(MOD_LALT)

// #define OSL_SYM OSL(SYM_LAYER)
// #define SYM MO(SYM_LAYER)
#define SYM OSL(SYM_LAYER)
// #define NAV MO(NAV_LAYER)
#define NAV OSL(NAV_LAYER)
#define NAVH MO(NAV_LAYER)
// #define OSL_NAV OSL(NAV_LAYER)
#define LNUM OSL(NUM_LAYER_LEFT)
#define RNUM OSL(NUM_LAYER_RIGHT)
#define OSM_SFT OSM(MOD_LSFT)

// #define SFT_A LSFT_T(KC_A)
// #define SFT_SCLN LSFT_T(KC_SCLN)
// #define SFT_V LSFT_T(KC_V)
// #define SFT_M LSFT_T(KC_M)

#define OS_CS OSM(MOD_LCTL | MOD_LSFT)
#define OS_CA OSM(MOD_LCTL | MOD_LALT)

#define SEL_ALL LCMD(KC_A)
#define COPY LCMD(KC_C)
#define PASTE LCMD(KC_V)
#define CUT LCMD(KC_X)
#define UNDO LCMD(KC_Z)
#define RELOAD LCMD(KC_R)
#define FIND LCMD(KC_F)
#define DEL_WD LALT(KC_DEL)
#define BSPC_WD LALT(KC_BSPC)
#define DEL_LN LCMD(KC_DEL)
#define BSPC_LN LCMD(KC_BSPC)
#define LEFT_WD LALT(KC_LEFT)
#define RIGHT_WD LALT(KC_RIGHT)
#define COMPLETE LCTL(KC_SPC)

#ifdef COMBO_ENABLE
#    include "keymap_combo.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE_LAYER] = LAYOUT_manuform_num(
     KC_PSCR,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
     KC_TAB,   KC_Q,     KC_W,   KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
     KC_ENT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT),
     KC_UP,    KC_DOWN, KC_LGUI, KC_LALT, OSM_SFT, NAV,     KC_HYPR,         KC_ENT,   SYM,  KC_SPC,     KC_LBRC, KC_RBRC, KC_LEFT, KC_RIGHT,
                                          KC_LCTL, KC_LCMD, KC_LALT,         KC_RALT,  KC_RCMD,  KC_RCTL
  ),

  [SYM_LAYER] = LAYOUT_manuform_num(
    _______, _______, KC_HASH, KC_LBRC, KC_RBRC, KC_PLUS,                            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, QK_BOOT,
    _______, KC_PERC, KC_GRV,  KC_EQL,  KC_AMPR, KC_PIPE,                            _______ ,  _______, _______, _______, _______, KC_F10,
    _______, KC_LT,    KC_GT,  KC_LPRN, KC_RPRN, KC_MINS,                            _______,  OS_RCMD, OS_RCTRL, OS_RALT,OS_RSHFT, KC_F11,
    _______, KC_BSLS, KC_EXLM, KC_LCBR, KC_RCBR, KC_UNDS,                            _______, _______, _______, _______, _______ , KC_F12,
    _______, _______, _______, _______, _______, NAV    , _______,         _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,         _______, _______, _______
  ),

  [SYM_MODS_LAYER] = LAYOUT_manuform_num(
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______  ,_______, _______,                           _______, OS_RCMD, OS_RCTRL, OS_RALT,OS_RSHFT, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,         _______, _______, _______
  ),

  [NAV_LAYER] = LAYOUT_manuform_num(
     QK_BOOT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_TILD,  KC_DLR, KC_ASTR,   KC_AT,   KC_CIRC, _______,
     _______, _______, COMPLETE, OSM_HYPR, RELOAD,  REPEAT,                            LEFT_WD,  KC_PGDN, KC_PGUP,RIGHT_WD, KC_HOME, RCTL(KC_P),
     _______, OS_LSHFT,OS_LALT, OS_LCTRL,OS_LCMD,  SW_WIN,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_END,  RCTL(KC_N),
     _______, UNDO,    CUT,     COPY,    PASTE,   SW_TAB,                            BSPC_WD, KC_BSPC, KC_DEL,  DEL_WD,   CODE_BLK, _______,
     _______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_TAB , _______, _______, _______, _______,
                                         _______, _______, _______,         _______, _______, _______
  ),

  [NAV_MODS_LAYER] = LAYOUT_manuform_num(
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, OS_LSHFT,OS_LALT, OS_LCTRL,OS_LCMD,  CLR_NAV,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,         _______, _______, _______
  ),

  [NUM_LAYER_LEFT] = LAYOUT_manuform_num(
    _______, _______, _______,  _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, KC_1,    KC_2,    KC_3,    _______,                            _______, _______, _______, _______, _______, _______,
    _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_DOT,                             _______, _______, _______, _______, _______, _______,
    _______, _______, KC_7,    KC_8,    KC_9,    _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,         _______, _______, _______
  ),
  [NUM_LAYER_RIGHT] = LAYOUT_manuform_num(
    _______, _______, _______,  _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, KC_1,    KC_2,    KC_3,    _______,                            _______, KC_1,    KC_2,    KC_3,    _______, _______,
    _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_DOT,                             KC_DOT,  KC_4,    KC_5,    KC_6,    KC_0,    _______,
    _______, _______, KC_7,    KC_8,    KC_9,    _______,                            _______, KC_7,    KC_8,    KC_9,    _______, _______,
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,         _______, _______, _______
  ),

  [CLR_NAV_LAYER] = LAYOUT_manuform_num(
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, CLR_NAV,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,         _______, _______, _______
  )

  /* Template */
  // [CLR_NAV_LAYER] = LAYOUT_manuform_num(
  //   _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  //   _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  //   _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  //   _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  //   _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  //                                       _______, _______, _______,         _______, _______, _______
  // )


};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        // case OSL_NAV:
        // case NUM:
        case KC_HYPR:
        case OSM_HYPR:
        case KC_LGUI:
        case KC_LCTL:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case NAV:
        case SYM:
        case LNUM:
        case RNUM:
        case KC_LSFT:
        case OS_LSHFT:
        case OS_LCTRL:
        case OS_LALT:
        case OS_LCMD:
        case OS_RSHFT:
        case OS_RCTRL:
        case OS_RALT:
        case OS_RCMD:
        case CLR_NAV:
            return true;
        default:
            return false;
    }
}
void on_before_oneshot_mod_activate(oneshot_mod_state *mod_state, uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OS_LSHFT:
        case OS_LCTRL:
        case OS_LALT:
        case OS_LCMD:
            layer_off(NAV_LAYER);
            layer_on(NAV_MODS_LAYER);
            break;
        case OS_RSHFT:
        case OS_RCTRL:
        case OS_RALT:
        case OS_RCMD:
            layer_off(SYM_LAYER);
            layer_on(SYM_MODS_LAYER);
            break;
    }
}
void on_before_oneshot_mod_cancel(oneshot_mod_state *mod_state, uint16_t keycode, keyrecord_t *record) {
    layer_off(SYM_MODS_LAYER);
    layer_off(NAV_MODS_LAYER);
    if (mod_state->state == os_down_used) {
        switch (keycode) {
            case KC_LEFT:
            case KC_DOWN:
            case KC_UP:
            case KC_RGHT:
                layer_on(NAV_LAYER);
                break;
        }
    }
}

void on_before_oneshot_deferred_mod_cancel(oneshot_mod_state *mod_state) {
    layer_off(SYM_MODS_LAYER);
    layer_off(NAV_MODS_LAYER);
}

void process_snippets(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CODE_BLK:
                SEND_STRING("```\n\n```" SS_TAP(X_UP));
                break;
            case SN1:
                SEND_STRING("()=>{}" SS_TAP(X_LEFT));
                break;
            case SN2:
                SEND_STRING("=>");
                break;
            case SN3:
                SEND_STRING("===");
                break;
            case SN4:
                SEND_STRING("{}" SS_TAP(X_LEFT) SS_TAP(X_ENTER));
                break;
        }
    }
}

void process_oneshot_symbols(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        switch (keycode) {
            /* case KC_LBRC: */
            /* case KC_RBRC: */
            case KC_PERC:
            /* case KC_GRV: */
            /* case KC_EQL: */
            /* case KC_AMPR: */
            /* case KC_PIPE: */
            /* case KC_DQT: */
            /* case KC_QUOT: */
            /* case KC_LPRN: */
            /* case KC_RPRN: */
            /* case KC_MINS: */
            case KC_BSLS:
            case KC_EXLM:
            case KC_LCBR:
            case KC_RCBR:
            /* case KC_UNDS: */
            case KC_TILD:
            case KC_DLR:
            case KC_ASTR:
            case KC_AT:
            case KC_CIRC:
            case KC_PLUS:
            case KC_HASH:
                layer_off(SYM_LAYER);
                break;
        }
    }
}

void process_layer(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // turn off sym layer when NAV button is pressed, this is to avoid getting stuck
        // in SYM layer when pressing SYM+NAV+key
        case NAV:
            if (record->event.pressed) {
                layer_off(SYM_LAYER);
                layer_off(NUM_LAYER_LEFT);
                layer_off(NUM_LAYER_RIGHT);
                layer_off(SYM_MODS_LAYER);
                layer_off(NAV_MODS_LAYER);
                layer_off(CLR_NAV_LAYER);
            }
            break;
        case SYM:
            if (record->event.pressed) {
                layer_off(NAV_LAYER);
                layer_off(NUM_LAYER_LEFT);
                layer_off(NUM_LAYER_RIGHT);
                layer_off(SYM_MODS_LAYER);
                layer_off(NAV_MODS_LAYER);
                layer_off(CLR_NAV_LAYER);
            }
            break;
        case CLR_NAV:
            if (record->event.pressed) {
                layer_off(NAV_LAYER);
                layer_off(NAV_MODS_LAYER);
                layer_on(CLR_NAV_LAYER);
            } else {
                layer_off(CLR_NAV_LAYER);
            }
            break;
    }
}

int            one_shift_state = 0;
deferred_token one_shift_token = 0;

uint32_t cancelOneShift(uint32_t trigger_time, void *cb_arg) {
    one_shift_state = 0;
    unregister_mods(MOD_BIT(KC_LSFT));
    return 0;
}

void process_one_shift(uint16_t keycode, keyrecord_t *record) {
    if (keycode == ONE_SHIFT) {
        if (record->event.pressed) {
            if (is_caps_word_on()) {
                caps_word_off();
                return;
            }

            if (one_shift_state == 2) {
                // double tapped shift
                one_shift_state = -1;
                unregister_mods(MOD_BIT(KC_LSFT));
                cancel_deferred_exec(one_shift_token);
                return;
            }

            cancel_deferred_exec(one_shift_token);
            one_shift_state = 2;
            register_mods(MOD_BIT(KC_LSFT));
        } else {
            if (one_shift_state == -1) {
                one_shift_state = 0;
                caps_word_on();
            } else if (one_shift_state == -2) {
                one_shift_state = 0;
                unregister_mods(MOD_BIT(KC_LSFT));
            } else {
                one_shift_token = defer_exec(ONESHOT_TIMEOUT, cancelOneShift, NULL);
            }
        }
    } else if (record->event.pressed && one_shift_state > 0) {
        switch (keycode) {
            // Keycodes that kill shift.
            case KC_A ... KC_Z:
                if (one_shift_state == 1) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                }
                one_shift_state--;
                break;

            default:
                cancel_deferred_exec(one_shift_token);
                one_shift_state = -2;
                return;
        }
    }
}

typedef struct {
    uint16_t       key;
    uint8_t        layer;
    int            state;
    deferred_token dtoken;
} oneshot_sym_config;

uint32_t cancelOneSym(uint32_t trigger_time, void *cb_arg) {
    oneshot_sym_config *config = (oneshot_sym_config *)cb_arg;
    layer_off(config->layer);
    config->state = 0;
    return 0;
}

void process_one_sym(uint16_t keycode, keyrecord_t *record, oneshot_sym_config *config) {
    if (keycode == config->key) {
        if (record->event.pressed) {
            cancel_deferred_exec(config->dtoken);
            config->state = 2;
            layer_on(config->layer);
        } else {
            config->dtoken = defer_exec(ONESHOT_TIMEOUT, cancelOneSym, config);
        }
    } else if (record->event.pressed && config->state > 0) {
        if (config->state == 1) {
            layer_off(config->layer);
        }
        config->state--;
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_mod_state os_lshft_state = {.mod = KC_LSFT, .state = os_up_unqueued};
oneshot_mod_state os_lctrl_state = {.mod = KC_LCTL, .state = os_up_unqueued};
oneshot_mod_state os_lalt_state  = {.mod = KC_LALT, .state = os_up_unqueued};
oneshot_mod_state os_lcmd_state  = {.mod = KC_LCMD, .state = os_up_unqueued};

oneshot_mod_state os_rshft_state = {.mod = KC_LSFT, .state = os_up_unqueued};
oneshot_mod_state os_rctrl_state = {.mod = KC_LCTL, .state = os_up_unqueued};
oneshot_mod_state os_ralt_state  = {.mod = KC_LALT, .state = os_up_unqueued};
oneshot_mod_state os_rcmd_state  = {.mod = KC_LCMD, .state = os_up_unqueued};

uint16_t get_mod_for_key_right(uint16_t keycode) {
    uint16_t res = 0;
    switch (keycode) {
        case OS_RSHFT:
            res = KC_LSFT;
            break;
        case OS_RCTRL:
            res = KC_LCTL;
            break;
        case OS_RALT:
            res = KC_LALT;
            break;
        case OS_RCMD:
            res = KC_LCMD;
            break;
    }

    return res;
}

oneshot_group_mod_config oneshot_group_right = {.state = OSG_STATE_DISABLED, .layer = SYM_MODS_LAYER, .get_mod_for_key = &get_mod_for_key_right, .is_ignored_key = &is_oneshot_ignored_key, .is_cancel_key = &is_oneshot_cancel_key};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // window swapper
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    update_swapper(&sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, keycode, record);

    // oneshot mods
    update_oneshot(&os_lshft_state, OS_LSHFT, keycode, record);
    update_oneshot(&os_lctrl_state, OS_LCTRL, keycode, record);
    update_oneshot(&os_lalt_state, OS_LALT, keycode, record);
    update_oneshot(&os_lcmd_state, OS_LCMD, keycode, record);

    update_oneshot(&os_rshft_state, OS_RSHFT, keycode, record);
    update_oneshot(&os_rctrl_state, OS_RCTRL, keycode, record);
    update_oneshot(&os_ralt_state, OS_RALT, keycode, record);
    update_oneshot(&os_rcmd_state, OS_RCMD, keycode, record);
    /* update_oneshot_group(&oneshot_group_right, keycode, record); */

    // repeat last key
    process_repeat_key(REPEAT, keycode, record);

    // snippets
    process_snippets(keycode, record);

    process_layer(keycode, record);

    /* process_oneshot_symbols(keycode, record); */

    /* process_one_shift(keycode, record); */

    return true;
}

#ifdef COMBO_ENABLE
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(BASE_LAYER) || layer_state_is(NAV_MODS_LAYER) || layer_state_is(SYM_MODS_LAYER)) {
        return true;
    }
    return false;
}
#endif
