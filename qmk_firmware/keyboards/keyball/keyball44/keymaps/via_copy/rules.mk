RGBLIGHT_ENABLE = no

OLED_ENABLE = yes

VIA_ENABLE = yes
LTO_ENABLE = yes

SRC += features/luna.c
WPM_ENABLE = yes
COMBO_ENABLE = yes

# 未使用のレガシー機能を無効化(容量削減)
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
