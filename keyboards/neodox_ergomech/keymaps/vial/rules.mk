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
KEYBOARD_SHARED_EP = yes  # for the Apple Globe modifier
ERGOMECH_ANIMATION_ENABLE = yes
WPM_CHART_ENABLE = yes
OCEAN_DREAM_ENABLE = yes
SPACE_WPM_ENABLE = yes
LUNA_ENABLE = yes
SUPERLOOP_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
	ifeq ($(strip $(ERGOMECH_ANIMATION_ENABLE)), yes)
		SRC += ergomechstore_ani.c
		OPT_DEFS += -DERGOMECH_ANIMATION_ENABLE
    endif

	ifeq ($(strip $(WPM_CHART_ENABLE)), yes)
		SRC += wpm_chart.c
		OPT_DEFS += -DWPM_CHART_ENABLE
    endif

    ifdef OCEAN_DREAM_ENABLE
        ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
            SRC += ocean_dream.c
            OPT_DEFS += -DOCEAN_DREAM_ENABLE
        endif
    endif

	ifeq ($(strip $(SPACE_WPM_ENABLE)), yes)
		SRC += space_wpm.c
		OPT_DEFS += -DSPACE_WPM_ENABLE
    endif

	ifeq ($(strip $(LUNA_ENABLE)), yes)
		SRC += luna.c
		OPT_DEFS += -DLUNA_ENABLE
    endif

	ifeq ($(strip $(SUPERLOOP_ENABLE)), yes)
		SRC += superloop.c
		OPT_DEFS += -DSUPERLOOP_ENABLE
    endif
endif
