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

#include QMK_KEYBOARD_H

#include "keymap.h"

#ifdef OLED_ENABLE

#    ifdef WPM_CHART_ENABLE
#        include "wpm_chart.h"
#    endif
#    ifdef ERGOMECH_ANIMATION_ENABLE
#        include "ergomechstore_ani.h"
#    endif
#    ifdef SPACE_WPM_ENABLE
#        include "space_wpm.h"
#    endif
#    ifdef OCEAN_DREAM_ENABLE
#        include "ocean_dream.h"
#    endif
#    ifdef LUNA_ENABLE
#        include "luna.h"
#    endif
#    ifdef SUPERLOOP_ENABLE
#        include "superloop.h"
#    endif

enum animation { ANI_LUNA, ANI_WPM_GRAPH, ANI_ERGOMECH, ANI_OCEAN_DREAM, ANI_SPACE, ANI_SUPERLOOP, ANI_LAST };

static int8_t selected_animation = ANI_LUNA;
#endif

// define custom macro key codes
enum custom_keycodes {
    USER_00 = QK_KB, // these values show up on Vial as USERxx
    USER_01,
    USER_02,
    USER_03,
    USER_04,
    CMD_A = SAFE_RANGE, // these values show up on Vial as hex numbers. We don't tie custom behavior to standard Vial keycodes.
    CMD_Z,
    CMD_X,
    CMD_C,
    CMD_V,
    CTL_A,
    CTL_Z,
    CTL_X,
    CTL_C,
    CTL_V,
    KC_GLOBE,
    ANI_0,
    ANI_1,
    ANI_2,
    ANI_3
};

void install_combo_entries(void) {
    vial_combo_entry_t cb0 = {{USER_01, USER_02, USER_03, KC_NO}, QK_BOOTLOADER}; // shortcut to bootloader, lefthand side
    vial_combo_entry_t cb1 = {{KC_NO, KC_DOWN, KC_UP, KC_RIGHT}, QK_BOOTLOADER};  // shortcut to bootloader, righthand side
    vial_combo_entry_t cb2 = {{USER_00, KC_1, KC_NO, KC_NO}, TO(0)};              // shortcut to go to layer 0
    vial_combo_entry_t cb3 = {{USER_00, KC_2, KC_NO, KC_NO}, TO(1)};              // shortcut to go to layer 1
    vial_combo_entry_t cb4 = {{USER_00, KC_3, KC_NO, KC_NO}, TO(2)};              // shortcut to go to layer 2
    vial_combo_entry_t cb5 = {{USER_00, KC_4, KC_NO, KC_NO}, TO(3)};              // shortcut to go to layer 3

    dynamic_keymap_set_combo(0, &cb0);
    dynamic_keymap_set_combo(1, &cb1);
    dynamic_keymap_set_combo(2, &cb2);
    dynamic_keymap_set_combo(3, &cb3);
    dynamic_keymap_set_combo(4, &cb4);
    dynamic_keymap_set_combo(5, &cb5);
};

void install_tap_dance_entries(void) {
    // ctl/cmd modifier doubles up with (
    vial_tap_dance_entry_t td0 = {KC_LPRN, KC_LCTL, KC_NO, KC_NO, 150}; // hold=ctl, tap=( for Mac layers
    vial_tap_dance_entry_t td1 = {KC_LPRN, KC_LGUI, KC_NO, KC_NO, 150}; // hold=gui, tap=( for Win layers

    // Apple Globe key
    vial_tap_dance_entry_t td7 = {KC_TAB, KC_GLOBE, KC_NO, KC_NO, 150}; // hold=Globe, tap=TAB

    // Cmd-A/Z/X/C/V shortcuts, simulated on the same physical postions as qwerty, but for the focal layout
    // apple
    vial_tap_dance_entry_t td2 = {KC_S, CMD_A, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td3 = {KC_Z, CMD_Z, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td4 = {KC_X, CMD_X, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td5 = {KC_M, CMD_C, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td6 = {KC_D, CMD_V, KC_NO, KC_NO, TAPPING_TERM};
    // windows
    vial_tap_dance_entry_t td8  = {KC_S, CTL_A, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td9  = {KC_Z, CTL_Z, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td10 = {KC_X, CTL_X, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td11 = {KC_M, CTL_C, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td12 = {KC_D, CTL_V, KC_NO, KC_NO, TAPPING_TERM};

    dynamic_keymap_set_tap_dance(0, &td0);
    dynamic_keymap_set_tap_dance(1, &td1);
    dynamic_keymap_set_tap_dance(2, &td7);
    dynamic_keymap_set_tap_dance(3, &td2);
    dynamic_keymap_set_tap_dance(4, &td3);
    dynamic_keymap_set_tap_dance(5, &td4);
    dynamic_keymap_set_tap_dance(6, &td5);
    dynamic_keymap_set_tap_dance(7, &td6);
    dynamic_keymap_set_tap_dance(8, &td8);
    dynamic_keymap_set_tap_dance(9, &td9);
    dynamic_keymap_set_tap_dance(10, &td10);
    dynamic_keymap_set_tap_dance(11, &td11);
    dynamic_keymap_set_tap_dance(12, &td12);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_GLOBE:
            host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false;
    }

    // Handle Cmd/Ctl shortcuts for alt layouts
    if (!record->event.pressed) {
        switch (keycode) {
            case CMD_A:
                SEND_STRING(SS_LCMD("a"));
                return false;
            case CMD_Z:
                SEND_STRING(SS_LCMD("z"));
                return false;
            case CMD_X:
                SEND_STRING(SS_LCMD("x"));
                return false;
            case CMD_C:
                SEND_STRING(SS_LCMD("c"));
                return false;
            case CMD_V:
                SEND_STRING(SS_LCMD("v"));
                return false;
            case CTL_A:
                SEND_STRING(SS_LCTL("a"));
                return false;
            case CTL_Z:
                SEND_STRING(SS_LCTL("z"));
                return false;
            case CTL_X:
                SEND_STRING(SS_LCTL("x"));
                return false;
            case CTL_C:
                SEND_STRING(SS_LCTL("c"));
                return false;
            case CTL_V:
                SEND_STRING(SS_LCTL("v"));
                return false;
        }
    }

#ifdef OLED_ENABLE
    // wait for release of animation cycle buttons
    if (!record->event.pressed) {
        switch (keycode) {
            case ANI_0:
                selected_animation = (selected_animation + 1) % ANI_LAST;
                if (selected_animation == ANI_WPM_GRAPH) wpm_reset();
                oled_init(OLED_ROTATION_0);
                break;
            case ANI_1:
                selected_animation = (selected_animation - 1 + ANI_LAST) % ANI_LAST;
                if (selected_animation == ANI_WPM_GRAPH) wpm_reset();
                oled_init(OLED_ROTATION_0);
                break;
        }
    }

#    ifdef OCEAN_DREAM_ENABLE
    // Handle Ocean Dream animation
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
        case KC_LGUI:
        case KC_RGUI:
        case TD_CTL_LP:
        case MT_CTL_DEL:
        case TD_GUI_LP:
        case MT_GUI_DEL:
            is_calm = (record->event.pressed) ? true : false;
            break;
    }
#    endif

#    ifdef LUNA_ENABLE
    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
        case MT_SHT_BSP:
            isSneaking = record->event.pressed;
            break;
        case KC_LCTL:
        case KC_RCTL:
        case KC_LGUI:
        case KC_RGUI:
        case TD_CTL_LP:
        case MT_CTL_DEL:
        case TD_GUI_LP:
        case MT_GUI_DEL:
            isBarking = record->event.pressed;
            break;
        case LT_MNA_SPC:
        case LT_WNA_SPC:
        case KC_SPC:
            isJumping = record->event.pressed;
            if (record->event.pressed) {
                showedJump = false;
            }
            break;
    }
#    endif

    return true;
};

// clang-format off
const char *layer_names[] = {
    [_MQWE] = "Qwrty",
    [_MFOC] = "Focal",
    [_WQWE] = "Qwrty",
    [_WFOC] = "Focal",
    [_MNAV] = "Navig",
    [_WNAV] = "Navig",
    [_SYMB] = "Symbl",
    [_FUNC] = "F1-12"
};

const uint8_t layer_oses[] = {
    [_MQWE] = OS_MACOS,
    [_MFOC] = OS_MACOS,
    [_WQWE] = OS_WINDOWS,
    [_WFOC] = OS_WINDOWS,
    [_MNAV] = OS_MACOS,
    [_WNAV] = OS_WINDOWS,
    [_SYMB] = OS_UNSURE,
    [_FUNC] = OS_UNSURE
};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MQWE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,                                            KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINUS,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,USER_00 ,                          KC_MPLY ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TD_GLB_TB,KC_A   ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,XXXXXXX ,                          KC_MUTE ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TD_CTL_LP,KC_Z   ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_LPRN ,KC_RPRN ,        KC_LBRC ,KC_RBRC ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RPRN ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     USER_01 ,USER_02 ,USER_03 ,MT_ALT_ENT, MT_GUI_DEL,MT_SHT_BSP,MT_ALT_ENT,        LT_FN_EQL,LT_MNA_SPC,LT_SYM_MIN    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_MFOC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_V    ,KC_L    ,KC_H    ,KC_G    ,KC_K    ,_______ ,                          _______ ,KC_Q    ,KC_F 	,KC_O    ,KC_U    ,KC_J    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,TD_S_CA ,KC_R    ,KC_N    ,KC_T    ,KC_B    ,_______ ,                          _______ ,KC_Y    ,KC_C 	,KC_A    ,KC_E    ,KC_I    ,KC_SLSH ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,TD_Z_CZ ,TD_X_CX ,TD_M_CC ,TD_D_CV ,KC_P    ,_______ ,_______ ,        _______ ,_______ ,KC_QUOT ,KC_W 	,KC_DOT  ,KC_SCLN ,KC_COMM ,KC_RPRN ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_WQWE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TD_GUI_LP,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    MT_CTL_DEL,_______,       LT_WNA_SPC,_______,   _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_WFOC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_V    ,KC_L    ,KC_H    ,KC_G    ,KC_K    ,_______ ,                          _______ ,KC_Q    ,KC_F 	,KC_O    ,KC_U    ,KC_J    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,TD_S_CLA,KC_R    ,KC_N    ,KC_T    ,KC_B    ,_______ ,                          _______ ,KC_Y    ,KC_C 	,KC_A    ,KC_E    ,KC_I    ,KC_SLSH ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TD_GUI_LP,TD_Z_CLZ,TD_X_CLX,TD_M_CLC,TD_D_CLV,KC_P   ,_______ ,_______ ,        _______ ,_______ ,KC_QUOT ,KC_W 	,KC_DOT  ,KC_SCLN ,KC_COMM ,KC_RPRN ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    MT_CTL_DEL,_______,       LT_WNA_SPC,_______,   _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_MNAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   , KC_F6  ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,KC_BTN1 ,KC_MS_U ,KC_BTN2 ,KC_WH_U ,_______ ,                          _______ ,OPT_UP  ,OPT_LE  ,KC_UP   ,OPT_RI  ,GUI_UP  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,_______ ,                          _______ ,OPT_DN  ,KC_LEFT ,KC_DOWN ,KC_RIGHT,GUI_DN  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,GUI_LE  ,XXXXXXX ,GUI_RI  ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

   [_WNAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   , KC_F6  ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,KC_BTN1 ,KC_MS_U ,KC_BTN2 ,KC_WH_U ,_______ ,                          _______ ,KC_PGUP ,CTL_LE  ,KC_UP   ,CTL_RI  ,CTL_HOM ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,_______ ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,CTL_END ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_HOME ,XXXXXXX ,KC_END  ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

   [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   , KC_F6  ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV  ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,_______ ,                          XXXXXXX ,KC_DOT  ,KC_1    ,KC_2    ,KC_3    ,KC_PLUS ,KC_PERC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TILD ,KC_CIRC ,KC_PIPE ,KC_AMPR ,KC_LCBR ,KC_LBRC ,XXXXXXX ,                          XXXXXXX ,KC_0    ,KC_4    ,KC_5    ,KC_6    ,KC_MINUS,KC_ASTR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_RCBR ,KC_RBRC ,KC_LPRN ,KC_RPRN ,        KC_LBRC ,KC_RBRC ,KC_COMMA,KC_7    ,KC_8    ,KC_9    ,KC_SLSH ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

   [_FUNC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   , KC_F6  ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,RGB_SAI ,RGB_HUI ,RGB_SPI ,XXXXXXX ,_______ ,                          XXXXXXX ,XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,RGB_SAD ,RGB_HUD ,RGB_SPD ,XXXXXXX ,RGB_TOG ,                          BL_TOGG ,XXXXXXX ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RGB_RMOD,RGB_MOD ,        BL_STEP ,BL_BRTG ,XXXXXXX ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

    [8] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,QK_BOOT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

    [9] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,QK_BOOT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};
// clang-format on

void keyboard_post_init_user(void) {
    install_combo_entries();
    install_tap_dance_entries();
};

// basic logo drawing stuff
static void render_logo(const char *logo) {
    oled_write_P(logo, false);
}

// clang-format off
// static const char PROGMEM mac_logo[] = {0x95, 0x96, 0x0d, 0xb5, 0xb6, 0x0d, 0};
// static const char PROGMEM win_logo[] = {0x97, 0x98, 0x0d, 0xb7, 0xb8, 0x0d, 0};
// static const char PROGMEM tux_logo[] = {0x99, 0x9a, 0x0d, 0xb9, 0xba, 0x0d, 0};
// static const char PROGMEM wtf_logo[] = {0x9d, 0x9e, 0x0d, 0xbd, 0xbe, 0x0d, 0};

/* The standard QMK logo */
static const char PROGMEM qmk_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0
 };
// clang-format on

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        switch (selected_animation) {
            case ANI_LUNA:
            case ANI_WPM_GRAPH:
            case ANI_ERGOMECH:
            case ANI_OCEAN_DREAM:
            case ANI_SUPERLOOP:
                return OLED_ROTATION_270;
            case ANI_SPACE:
                return OLED_ROTATION_0;
            default:
                return rotation;
        }
    } else {
        return OLED_ROTATION_180;
    }
}

bool oled_task_user(void) {
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return false;
    }

    if (is_keyboard_master()) {
        switch (selected_animation) {
            case ANI_LUNA:
                print_status_luna();
                break;
            case ANI_WPM_GRAPH:
                render_wpm_chart();
                break;
            case ANI_ERGOMECH:
                render_ergo_logo();
                break;
            case ANI_OCEAN_DREAM:
                render_stars();
                break;
            case ANI_SPACE:
                render_space();
                break;
            case ANI_SUPERLOOP:
                render_superloop();
                break;
            default:
                render_logo(qmk_logo);
        }
    } else {
        render_logo(qmk_logo);
    }
    return true;
}

#endif

#if defined(ENCODER_MAP_ENABLE)

// clang-format off
const uint16_t PROGMEM encoder_map[][2][2] = {
    [_MQWE] = { ENCODER_CCW_CW(ANI_0, ANI_1),          ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [_MFOC] = { ENCODER_CCW_CW(_______, _______),      ENCODER_CCW_CW(_______, _______)  },
    [_WQWE] = { ENCODER_CCW_CW(_______, _______),      ENCODER_CCW_CW(_______, _______)  },
    [_WFOC] = { ENCODER_CCW_CW(_______, _______),      ENCODER_CCW_CW(_______, _______)  },
    [_MNAV] = { ENCODER_CCW_CW(KC_DOWN, KC_UP),        ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
    [_WNAV] = { ENCODER_CCW_CW(KC_DOWN, KC_UP),        ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
    [_SYMB] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX),      ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_FUNC] = { ENCODER_CCW_CW(RGB_VAI, RGB_VAD),      ENCODER_CCW_CW(BL_UP, BL_DOWN) },
    [8] =     { ENCODER_CCW_CW(XXXXXXX, XXXXXXX),      ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [9] =     { ENCODER_CCW_CW(XXXXXXX, XXXXXXX),      ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },

    //                  Encoder 1                                     Encoder 2
};
// clang-format on

#endif
