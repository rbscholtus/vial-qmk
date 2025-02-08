/* MIT License
 *
 * Copyright (c) 2021 hexcowboy
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

// adjust the animation speed
#define BASE_DELAY 400       // delay between frames
#define LESS_DELAY_PER_WPM 4 // decrease the delay per frame by wpm * this
#define MIN_DELAY 20         // minimum delay, to prevent choking the MCU

// number of animation frames in the data
#define SLOOP_FRAMES 8 // number of frames

void render_superloop(void);
