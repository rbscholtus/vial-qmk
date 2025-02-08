/* Copyright 2025 Barend Scholtus
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

// The spaceship animation by /u/dmiralalleki
// https://github.com/JBaguley/qmk_firmware/tree/crkbd-retrograde-keymap/keyboards/crkbd/keymaps/retrograde
// Can be changed to any graphic by
// generating the imagedata here: https://javl.github.io/image2cpp/
// (set Draw mode to Vertical), and adjusting the settings below.
// In rules.mk, add: SRC += spaceship.c
//              and: OPT_DEFS += -DSPACESHIP_ANIMATION_ENABLE
// In keymap.c, add: #include "spaceship.h"
// In oled_init_user(), set rotation to OLED_ROTATION_270
// In oled_task_user(), call render_ergo_logo()

#pragma once

#include QMK_KEYBOARD_H

#define SP_SCREEN_WIDTH 32    // screen pixels width. this is how many pixels we will draw and scroll.
#define SP_SCREEN_HEIGHT 128  // screen pixels height. ignored.
#define SP_IMAGE_HEIGHT 128   // image height in memory. it must be a multiple of 8.
#define SP_IDLE_SPEED 1       // pixels per frame of scrolling even without typing
#define SP_WPM_SPEED_DIV 15   // additionally, scroll this nr of pixels per frame: wpm / WPM_SPEED_DIV. Set to 241 or higher to disable
#define SP_FRAME_DELAY_MS 100 // delay in ms between frames

void render_space(void);
