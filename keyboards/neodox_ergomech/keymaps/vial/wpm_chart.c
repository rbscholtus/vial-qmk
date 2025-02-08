/* Copyright 2020 Barend Scholtus
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

#include "wpm_chart.h"

#include QMK_KEYBOARD_H

#include "keymap.h"

static uint32_t last_render_time              = 0;
static uint8_t  new_wpm                       = 0;
static uint8_t  wpm_history[WPM_HISTORY_SIZE] = {0};
static uint8_t  curr_hist_idx                 = 0;
static uint8_t  max_wpm                       = 0;
static uint8_t  chart_max_wpm                 = 0;
static uint8_t  wpm_per_pix                   = 1;
static uint32_t total_wpm                     = 0; // Sum of all WPM values
static uint32_t total_wpm_entries             = 0; // Number of recorded WPM values
#ifdef TOP10CALC
static uint8_t top10_history[TOP10_SIZE] = {0}; // Store the top 10 WPM values
static uint8_t top10_avg                 = 0;
static bool    top10_do_calc             = true;
#endif

void update_all_time_avg(uint8_t new_wpm) {
    if (new_wpm > 0) {
        total_wpm += new_wpm;
        total_wpm_entries++;
    }
}

uint8_t get_all_time_avg(void) {
    return total_wpm_entries ? (total_wpm / total_wpm_entries) : 0;
}

#ifdef TOP10CALC
void insert_into_top10(uint8_t new_wpm) {
    uint8_t idx = 0;
    while (idx < TOP10_SIZE && new_wpm > top10_history[idx]) {
        if (idx > 0) top10_history[idx - 1] = top10_history[idx];
        idx++;
    }
    if (idx > 0) {
        top10_history[idx - 1] = new_wpm;
        top10_do_calc          = true;
    }
}

uint8_t get_top10_avg(void) {
    if (top10_do_calc) {
        uint16_t sum   = 0;
        uint8_t  count = 0;

        for (uint8_t i = 0; i < TOP10_SIZE; i++) {
            if (top10_history[i] > 0) {
                sum += top10_history[i];
                count++;
            }
        }

        top10_avg     = count ? sum / count : 0;
        top10_do_calc = false;
    }

    return top10_avg;
}
#endif

void update_wpm_history(void) {
    new_wpm                    = get_current_wpm();                      // Get current words per minute
    wpm_history[curr_hist_idx] = new_wpm;                                // Store it in the array
    curr_hist_idx              = (curr_hist_idx + 1) % WPM_HISTORY_SIZE; // Move index forward

    // calculate max wpm
    max_wpm       = MAX(max_wpm, new_wpm);
    chart_max_wpm = MAX(chart_max_wpm, new_wpm);

#ifdef TOP10CALC
    // top wpm
    insert_into_top10(new_wpm);
#endif

    // average wpm
    update_all_time_avg(new_wpm);

    // max to show on the chart
    // update this only sometimes
    if (curr_hist_idx == 0 || curr_hist_idx == WPM_HISTORY_SIZE / 2) {
        chart_max_wpm = wpm_history[0];
        for (uint8_t i = 1; i < WPM_HISTORY_SIZE; i++)
            chart_max_wpm = MAX(chart_max_wpm, wpm_history[i]);

        chart_max_wpm = MAX(chart_max_wpm, get_all_time_avg());
    }
}

void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t draw_every) {
    uint8_t draw_it = 0;

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; // Error term

    while (true) {
        oled_write_pixel(x0, y0, draw_it++ % draw_every == 0);
        if (x0 == x1 && y0 == y1) break; // End condition
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void render_chart(void) {
    // for scaling the Y axis
    wpm_per_pix = 1 + (chart_max_wpm * MARGIN_FACT / CHART_HEIGHT);

    // determine starting point of the chart
    uint8_t prev_x = CHART_ORIGIN_X;
    uint8_t prev_y = CHART_ORIGIN_Y - (wpm_history[curr_hist_idx % WPM_HISTORY_SIZE] / wpm_per_pix);

    // draw chart frame
    draw_line(CHART_ORIGIN_X, CHART_ORIGIN_Y, CHART_ORIGIN_X, CHART_ORIGIN_Y - CHART_HEIGHT + 1, 1);
    draw_line(CHART_ORIGIN_X, CHART_ORIGIN_Y, CHART_ORIGIN_X + WPM_HISTORY_SIZE - 1, CHART_ORIGIN_Y, 1);

    // draw avg line
    uint8_t avg_y = CHART_ORIGIN_Y - (get_all_time_avg() / wpm_per_pix);
    if (avg_y > 0) {
        draw_line(CHART_ORIGIN_X, avg_y, CHART_ORIGIN_X + WPM_HISTORY_SIZE - 1, avg_y, 3);
    }

    // draw chart
    for (uint8_t i = 1; i < WPM_HISTORY_SIZE; i++) {
        uint8_t x = CHART_ORIGIN_X + i;
        uint8_t y = CHART_ORIGIN_Y - (wpm_history[(curr_hist_idx + i) % WPM_HISTORY_SIZE] / wpm_per_pix);

        draw_line(prev_x, prev_y, x, y, 1);

        prev_x = x;
        prev_y = y;
    }
}

void write_text(void) {
    char buffer[4];

    // title
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("WPM"), false);

    // current wpm
    oled_set_cursor(2, 1);
    oled_write(get_u8_str(new_wpm, ' '), false);

    // Y axis title
    oled_set_cursor(0, 3);
    utoa(wpm_per_pix * CHART_HEIGHT, buffer, 10);
    oled_write(buffer, false);

    // Max, High and Average wpm

#ifdef TOP10CALC
    oled_set_cursor(0, 10);
    oled_write_P(PSTR("Max:"), false);
    oled_set_cursor(2, 11);
    oled_write(get_u8_str(max_wpm, ' '), false);

    oled_set_cursor(0, 12);
    oled_write_P(PSTR("High:"), false);
    oled_set_cursor(2, 13);
    oled_write(get_u8_str(get_top10_avg(), ' '), false);

    oled_set_cursor(0, 14);
    oled_write_P(PSTR("Avg:"), false);
    oled_set_cursor(2, 15);
    oled_write(get_u8_str(get_all_time_avg(), ' '), false);
#else
    oled_set_cursor(0, 12);
    oled_write_P(PSTR("Max:"), false);
    oled_set_cursor(2, 13);
    oled_write(get_u8_str(max_wpm, ' '), false);

    oled_set_cursor(0, 14);
    oled_write_P(PSTR("Avg:"), false);
    oled_set_cursor(2, 15);
    oled_write(get_u8_str(get_all_time_avg(), ' '), false);
#endif
}

void wpm_reset(void) {
    last_render_time = 0;
    new_wpm          = 0;
    memset(wpm_history, 0, sizeof(wpm_history)); // Reset the WPM history array
    curr_hist_idx     = 0;
    max_wpm           = 0;
    chart_max_wpm     = 0;
    wpm_per_pix       = 1;
    total_wpm         = 0;
    total_wpm_entries = 0;
#ifdef TOP10CALC
    memset(top10_history, 0, sizeof(top10_history)); // Reset top 10 WPM values
    top10_avg     = 0;
    top10_do_calc = true;
#endif
}

void render_wpm_chart(void) {
    if (timer_elapsed32(last_render_time) > CHART_TIME) {
        last_render_time = timer_read32();
        update_wpm_history();
        oled_clear();
        write_text();
        render_chart();
    }
}
