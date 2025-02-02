/* Copyright HarshitGoel96 2020
 * With permission from mattdibi, the original maintainer of the Redox hardware.
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

#ifdef OCEAN_DREAM_ENABLE
#    include "ocean_dream.h"
#endif

#include "keymap.h"
#include "oled.c"

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
    KC_GLOBE
};

void install_combo_entries(void) {
    vial_combo_entry_t cb0 = {{USER_01, USER_02, USER_03, USER_04}, QK_BOOTLOADER}; // shortcut to bootloader, lefthand side
    vial_combo_entry_t cb1 = {{KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT}, QK_BOOTLOADER};  // shortcut to bootloader, righthand side
    vial_combo_entry_t cb2 = {{USER_00, KC_1, KC_NO, KC_NO}, TO(0)};                // shortcut to go to layer 0
    vial_combo_entry_t cb3 = {{USER_00, KC_2, KC_NO, KC_NO}, TO(1)};                // shortcut to go to layer 1
    vial_combo_entry_t cb4 = {{USER_00, KC_3, KC_NO, KC_NO}, TO(2)};                // shortcut to go to layer 2
    vial_combo_entry_t cb5 = {{USER_00, KC_4, KC_NO, KC_NO}, TO(3)};                // shortcut to go to layer 3

    dynamic_keymap_set_combo(0, &cb0);
    dynamic_keymap_set_combo(1, &cb1);
    dynamic_keymap_set_combo(2, &cb2);
    dynamic_keymap_set_combo(3, &cb3);
    dynamic_keymap_set_combo(4, &cb4);
    dynamic_keymap_set_combo(5, &cb5);
};

void install_tap_dance_entries(void) {
    // ctl modifier doubles up with (
    vial_tap_dance_entry_t td0 = {KC_LPRN, KC_LCTL, KC_NO, KC_NO, 150}; // hold=ctl, tap=( for Mac layers
    vial_tap_dance_entry_t td1 = {KC_LPRN, KC_LGUI, KC_NO, KC_NO, 150}; // hold=gui, tap=( for Win layers

    // Cmd-A/Z/X/C/V shortcuts, simulated on the same physical postions as qwerty, but for the focal layout
    vial_tap_dance_entry_t td2 = {KC_S, CMD_A, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td3 = {KC_Z, CMD_Z, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td4 = {KC_X, CMD_X, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td5 = {KC_M, CMD_C, KC_NO, KC_NO, TAPPING_TERM};
    vial_tap_dance_entry_t td6 = {KC_D, CMD_V, KC_NO, KC_NO, TAPPING_TERM};

    // add Apple Globe key
    vial_tap_dance_entry_t td7 = {KC_TAB, KC_GLOBE, KC_NO, KC_NO, 150}; // hold=Globe, tap=TAB

    dynamic_keymap_set_tap_dance(0, &td0);
    dynamic_keymap_set_tap_dance(1, &td1);
    dynamic_keymap_set_tap_dance(2, &td2);
    dynamic_keymap_set_tap_dance(3, &td3);
    dynamic_keymap_set_tap_dance(4, &td4);
    dynamic_keymap_set_tap_dance(5, &td5);
    dynamic_keymap_set_tap_dance(6, &td6);
    dynamic_keymap_set_tap_dance(7, &td7);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_GLOBE:
            host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false;
    }

#ifdef OCEAN_DREAM_ENABLE
    // Handle Ocean Dream animation
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
            is_calm = (record->event.pressed) ? true : false;
            break;
        case USER_00:
            show_layout = (record->event.pressed) ? true : false;
            break;
    }
#endif

    // Handle Cmd shortcuts for alt layouts
    switch (keycode) {
        case CMD_A:
            if (!record->event.pressed) {
                SEND_STRING(SS_LCMD("a"));
            }
            return false;
        case CMD_Z:
            if (!record->event.pressed) {
                SEND_STRING(SS_LCMD("z"));
            }
            return false;
        case CMD_X:
            if (!record->event.pressed) {
                SEND_STRING(SS_LCMD("x"));
            }
            return false;
        case CMD_C:
            if (!record->event.pressed) {
                SEND_STRING(SS_LCMD("c"));
            }
            return false;
        case CMD_V:
            if (!record->event.pressed) {
                SEND_STRING(SS_LCMD("v"));
            }
            return false;
    }

    return true;
};

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
     USER_01 ,USER_02 ,USER_03 ,USER_04 ,   MT_ALT_ENT,  MT_SHT_BSP,MT_GUI_DEL,      LT_SYM_MIN,LT_MNA_SPC,LT_FN_EQL    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
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
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,MT_CTL_DEL,      _______, LT_WNA_SPC,  _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_WFOC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_V    ,KC_L    ,KC_H    ,KC_G    ,KC_K    ,_______ ,                          _______ ,KC_Q    ,KC_F 	,KC_O    ,KC_U    ,KC_J    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,TD_S_CA ,KC_R    ,KC_N    ,KC_T    ,KC_B    ,_______ ,                          _______ ,KC_Y    ,KC_C 	,KC_A    ,KC_E    ,KC_I    ,KC_SLSH ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TD_GUI_LP,TD_Z_CZ,TD_X_CX ,TD_M_CC ,TD_D_CV ,KC_P    ,_______ ,_______ ,        _______ ,_______ ,KC_QUOT ,KC_W 	,KC_DOT  ,KC_SCLN ,KC_COMM ,KC_RPRN ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,MT_CTL_DEL,      _______, LT_WNA_SPC,  _______ ,     _______ ,_______ ,_______ ,_______
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
     KC_GRV  ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,_______ ,                          XXXXXXX ,KC_DOT  ,KC_1    ,KC_2    ,KC_3    ,KC_PLUS ,XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TILD ,KC_CIRC ,KC_AMPR ,KC_LBRC ,KC_LPRN ,KC_LCBR ,XXXXXXX ,                          XXXXXXX ,KC_0    ,KC_4    ,KC_5    ,KC_6    ,KC_MINUS,KC_ASTR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,KC_PIPE ,KC_RBRC ,KC_RPRN ,KC_RCBR ,KC_LPRN ,KC_RPRN ,        KC_LBRC ,KC_RBRC ,KC_EQL  ,KC_7    ,KC_8    ,KC_9    ,KC_SLSH ,XXXXXXX ,
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

#if defined(ENCODER_MAP_ENABLE)

// clang-format off
const uint16_t PROGMEM encoder_map[][2][2] = {
    [_MQWE] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX),      ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
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
