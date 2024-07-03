SRC += features/oneshot.c
SRC += features/oled.c
SRC += features/swapper.c

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

RGBLIGHT_ENABLE = no
OLED_ENABLE     = yes
OLED_DRIVER     = ssd1306

LTO_ENABLE      = yes

AUTO_SHIFT_ENABLE = no
TAP_DANCE_ENABLE = no
CAPS_WORD_ENABLE = no
KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = no
DEFERRED_EXEC_ENABLE = no

CONSOLE_ENABLE = no
