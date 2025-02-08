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

#define CHART_TIME 500
#define WPM_HISTORY_SIZE 32
#define CHART_ORIGIN_X 0
#define MARGIN_FACT 1.1f
// #define TOP10CALC
#ifdef TOP10CALC
#    define CHART_ORIGIN_Y 72
#    define CHART_HEIGHT 40
#    define TOP10_SIZE 16
#else
#    define CHART_ORIGIN_Y 91
#    define CHART_HEIGHT 60
#endif

void render_wpm_chart(void);
void wpm_reset(void);
