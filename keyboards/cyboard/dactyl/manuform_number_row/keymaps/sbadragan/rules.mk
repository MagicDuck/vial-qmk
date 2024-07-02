SPLIT_KEYBOARD = yes
OLED_DRIVER_ENABLE  = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
AUTO_SHIFT_ENABLE = no
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

CONSOLE_ENABLE    = yes         # Console for debug(+400), run with `qmk console`
COMMAND_ENABLE    = no        # Commands for debug and configuration
AUDIO_ENABLE      = no
BACKLIGHT_ENABLE  = no
SWAP_HANDS_ENABLE = no
SPACE_CADET_ENABLE = no
INDICATOR_LIGHTS  = no
RGBLIGHT_TWINKLE  = no
RGBLIGHT_STARTUP_ANIMATION = no

EXTRAKEY_ENABLE = yes
LTO_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

SRC += oneshot.c
SRC += swapper.c
SRC += repeat.c
SRC += oneshot_group.c
