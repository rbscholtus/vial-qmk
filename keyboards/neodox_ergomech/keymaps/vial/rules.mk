VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes
CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
WPM_ENABLE = yes
OS_DETECTION_ENABLE = no
OCEAN_DREAM_ENABLE = yes
PERMISSIVE_HOLD = yes  # does not work on Vial UI

# https://github.com/snowe2010/qmk_firmware/blob/ocean-dream/users/snowe/readme_ocean_dream.md
ifeq ($(strip $(OLED_ENABLE)), yes)
    ifdef OCEAN_DREAM_ENABLE
        ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
            SRC += ocean_dream.c
            OPT_DEFS += -DOCEAN_DREAM_ENABLE
        endif
    endif
endif
