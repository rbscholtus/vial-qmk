/* Copyright Barend Scholtus 2025
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

#pragma once

#include QMK_KEYBOARD_H

// clang-format off

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _MQWE,
    _MFOC,
    _WQWE,
    _WFOC,
    _MNAV,
    _WNAV,
    _SYMB,
    _FUNC
};

enum os_layer {
    OS_UNSURE,
    OS_LINUX,
    OS_WINDOWS,
    OS_MACOS,
    OS_IOS,
};

// tap dance defines for readability
#define TD_CTL_LP TD(0)
#define TD_GUI_LP TD(1)
#define TD_GLB_TB TD(2)
#define TD_S_CA TD(3)
#define TD_Z_CZ TD(4)
#define TD_X_CX TD(5)
#define TD_M_CC TD(6)
#define TD_D_CV TD(7)
#define TD_S_CLA TD(8)
#define TD_Z_CLZ TD(9)
#define TD_X_CLX TD(10)
#define TD_M_CLC TD(11)
#define TD_D_CLV TD(12)

// mod tap and layer tap defines for readability
#define MT_ALT_ENT LALT_T(KC_ENT)
#define MT_GUI_DEL LGUI_T(KC_DEL)
#define MT_CTL_DEL LCTL_T(KC_DEL)
#define MT_SHT_BSP LSFT_T(KC_BSPC)
#define LT_MNA_SPC LT(_MNAV, KC_SPC)
#define LT_WNA_SPC LT(_WNAV, KC_SPC)
#define LT_SYM_MIN LT(_SYMB, KC_MINUS)
#define LT_FN_EQL LT(_FUNC, KC_EQL)

// Mac navigation defines for readability
#define OPT_UP LOPT(KC_UP)
#define OPT_DN LOPT(KC_DOWN)
#define OPT_LE LOPT(KC_LEFT)
#define OPT_RI LOPT(KC_RIGHT)
#define GUI_UP LGUI(KC_UP)
#define GUI_DN LGUI(KC_DOWN)
#define GUI_LE LGUI(KC_LEFT)
#define GUI_RI LGUI(KC_RIGHT)

// Win navigation defines for readability
#define CTL_HOM LCTL(KC_HOME)
#define CTL_END LCTL(KC_END)
#define CTL_LE LCTL(KC_LEFT)
#define CTL_RI LCTL(KC_RIGHT)

extern const char   *layer_names[];
extern const uint8_t layer_oses[];
