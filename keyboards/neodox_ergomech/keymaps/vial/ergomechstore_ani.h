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

// The Ergomech.store logo animation. Can be changed to any graphic by
// generating the imagedata here: https://javl.github.io/image2cpp/
// (set Draw mode to Vertical), and adjusting the settings below.
// In rules.mk, add: SRC += ergomechstore_logo.c
//              and: OPT_DEFS += -DERGOMECH_ANIMATION_ENABLE
// In keymap.c, add: #include "ergomechstore_logo.h"
// In oled_init_user(), set rotation to OLED_ROTATION_270
// In oled_task_user(), call render_ergo_logo()

#pragma once

#include "progmem.h"

#define EMS_SCREEN_WIDTH 32    // screen pixels width. this is how many pixels we will draw and scroll.
#define EMS_SCREEN_HEIGHT 128  // screen pixels height. ignored.
#define EMS_SCREEN_ROWS 16     // how many rows you want to print. each row has 8 pixels.
#define EMS_IMAGE_WIDTH 145    // width of your image in memory
#define EMS_IMAGE_HEIGHT 128   // image height in memory. it must be a multiple of 8.
#define EMS_BLANK_WIDTH 32     // blank pixels to appear after the image scrolled past
#define EMS_BLANK_COLOR 0      // the color of the blank pixels, 0 or 1
#define EMS_IDLE_SPEED 1       // pixels per frame of scrolling even without typing
#define EMS_WPM_SPEED_DIV 20   // additionally, scroll this nr of pixels per frame: wpm / WPM_SPEED_DIV. Set to 241 or higher to disable
#define EMS_FRAME_DELAY_MS 100 // delay in ms between frames
// #define EMS_WPM_POS_ROW 0      // row number where to show the WPM indicator, outcomment to disable completely
#define EMS_WPM_POS_COL 1     // column number where to show the WPM indicator (the number only)
#define EMS_WPM_INVERSE false // print WPM in inverted color true or false
// #define EMS_WPM_TITLE "WPM"   // title of WPM indicator, outcomment if not wanted
#define EMS_WPM_PAD_CHAR ' ' // left-padding to 3 characters of the counter, eg 0 or space

extern const char emstore_logo[] PROGMEM;

void render_ergo_logo(void);
