/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define VIAL_KEYBOARD_UID { 0x54, 0xB9, 0x18, 0x3D, 0xE9, 0x29, 0xA8, 0x22 }
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// https://get.vial.today/docs/porting-to-vial.html
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 } // top left and bottom left corner
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }

// tapping settings don't work on the Vial UI
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 100
#define HOLD_ON_OTHER_KEY_PRESS

// for the displays. oled_timeout is needed for Ocean dream to prevent screen off/on bug
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 10
#define OLED_TIMEOUT 60000

// https://docs.qmk.fm/features/oled_driver#logo-example
#define OLED_FONT_H "font.c"

// https://docs.qmk.fm/features/wpm
// #define WPM_SAMPLE_SECONDS 10
#define WPM_LAUNCH_CONTROL 1
