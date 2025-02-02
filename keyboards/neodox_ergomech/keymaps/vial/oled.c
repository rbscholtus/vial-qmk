/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Sets up what the OLED screens display.

#ifdef OLED_ENABLE

#    include "keymap.h"

#    include <stdio.h>

#    ifdef OCEAN_DREAM_ENABLE
#        include "ocean_dream.h"
#    endif

static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

#    ifndef OCEAN_DREAM_ENABLE
static const char PROGMEM mac_logo[] = {0x95, 0x96, 0x0d, 0xb5, 0xb6, 0x0d, 0};
static const char PROGMEM win_logo[] = {0x97, 0x98, 0x0d, 0xb7, 0xb8, 0x0d, 0};
static const char PROGMEM tux_logo[] = {0x99, 0x9a, 0x0d, 0xb9, 0xba, 0x0d, 0};
static const char PROGMEM wtf_logo[] = {0x9d, 0x9e, 0x0d, 0xbd, 0xbe, 0x0d, 0};
#    endif

static void render_logo(const char *logo) {
    oled_write_P(logo, false);
}

#    ifndef OCEAN_DREAM_ENABLE
static void render_os_logo(void) {
    switch (detected_host_os()) {
        case OS_MACOS:
        case OS_IOS:
            render_logo(mac_logo);
            break;
        case OS_WINDOWS:
            render_logo(win_logo);
            break;
        case OS_LINUX:
            render_logo(tux_logo);
            break;
        default:
            render_logo(wtf_logo);
            break;
    }
}

static void write_layout(void) {
    switch (get_highest_layer(layer_state)) {
        case _MQWE:
        case _WQWE:
            oled_write_P(PSTR("QWERTY"), false);
            break;
        case _MFOC:
        case _WFOC:
            oled_write_P(PSTR("FOCAL "), false);
            break;
        case _MNAV:
        case _WNAV:
            oled_write_P(PSTR("NAV   "), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("SYMBLS"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("F-KEYS"), false);
            break;
        default:
            oled_write_P(PSTR("UNSURE"), false);
            break;
    }
}

static void write_layout2(void) {
    switch (get_highest_layer(layer_state)) {
        case _MQWE:
        case _MFOC:
        case _MNAV:
            oled_write_P(PSTR("Mac   "), false);
            break;
        case _WQWE:
        case _WFOC:
        case _WNAV:
            oled_write_P(PSTR("Win   "), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("NUMBRS"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("LEDS  "), false);
            break;
        default:
            oled_write_P(PSTR("ANY   "), false);
            break;
    }
}

static void write_wpm(void) {
    char wpm_str[4]; // 3 characters + null terminator
    snprintf(wpm_str, sizeof(wpm_str), "%3d", get_current_wpm());
    oled_write(wpm_str, false);
}

static void write_lock_keys(uint8_t col) {
    led_t led_usb_state = host_keyboard_led_state();
    oled_set_cursor(col, 0);
    oled_write_P(PSTR("CAPS"), led_usb_state.caps_lock);
    oled_set_cursor(col, 1);
    oled_write_P(PSTR("NUM"), led_usb_state.num_lock);
    oled_set_cursor(col, 2);
    oled_write_P(PSTR("SCRL"), led_usb_state.scroll_lock);
}

static void render_status(void) {
    oled_set_cursor(0, 0);
    render_os_logo();
    oled_set_cursor(0, 3);
    oled_write_P("OS", false);

    oled_set_cursor(4, 0);
    write_layout();
    oled_set_cursor(4, 1);
    write_layout2();
    oled_set_cursor(4, 3);
    oled_write_P("layout", false);

    oled_set_cursor(12, 1);
    write_wpm();
    oled_set_cursor(12, 3);
    oled_write_P("WPM", false);

    write_lock_keys(17);
    oled_set_cursor(17, 3);
    oled_write_P("LOCK", false);
}

void write_simple_layer(void) {
    oled_set_cursor(0, 3);
    switch (get_highest_layer(layer_state)) {
        case _MQWE:
        case _WQWE:
            oled_write_P(PSTR("qwerty"), false);
            break;
        case _MFOC:
        case _WFOC:
            oled_write_P(PSTR("focal"), false);
            break;
        case _MNAV:
        case _WNAV:
            oled_write_P(PSTR("nav"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("sym+nr"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("f+leds"), false);
            break;
        default:
            oled_write_P(PSTR(" "), false);
            break;
    }
    switch (get_highest_layer(layer_state)) {
        case _MQWE:
        case _MFOC:
        case _MNAV:
            oled_write_P(PSTR("on Mac"), false);
            break;
        case _WQWE:
        case _WFOC:
        case _WNAV:
            oled_write_P(PSTR("on Win"), false);
            break;
        case _SYMB:
        case _FUNC:
        default:
            oled_write_P(PSTR(" "), false);
            break;
    }
}
#    endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    } else {
#    ifdef OCEAN_DREAM_ENABLE
        return OLED_ROTATION_270;
#    else
        return rotation;
#    endif
    }
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        render_logo(qmk_logo);
        // write_simple_layer();
    } else {
#    ifdef OCEAN_DREAM_ENABLE
        render_stars();
#    else
        render_status(); // requires OS_DETECTION_ENABLE = yes
#    endif
    }
    return true;
}

#endif
