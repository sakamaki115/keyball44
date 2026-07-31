RGBLIGHT_ENABLE = no

OLED_ENABLE = yes

VIA_ENABLE = yes
LTO_ENABLE = yes

SRC += features/achordion.c
SRC += qmk-vim/src/mac_mode.c
SRC += qmk-vim/src/process_func.c
SRC += qmk-vim/src/numbered_actions.c
SRC += qmk-vim/src/motions.c
SRC += qmk-vim/src/actions.c
SRC += qmk-vim/src/modes.c
SRC += qmk-vim/src/vim.c
COMBO_ENABLE = yes

# 未使用のレガシー機能を無効化(容量削減)
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
