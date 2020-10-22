/* Copyright 2019 Maarten Dekkers <maartenwut@gmail.com>
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
#include "eon75.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    led_init_ports();
};

void led_init_ports(void) {
    // * Set our LED pins as output and high
    setPinOutput(D5);
    writePinHigh(D5);
    
    setPinOutput(B7);
    writePinHigh(B7);
    
    setPinOutput(B0);
    writePinHigh(B0);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(D5, !led_state.caps_lock);
        writePin(B7, !led_state.num_lock);
        writePin(B0, !led_state.scroll_lock);
    }

    return true;
}
