/* Copyright 2012 Jun Wako <wakojun@gmail.com>: LED init
 * Copyright 2017 Mathias Andersson <wraul@dbox.se>: Phantom config
 * Copyright 2018 bakageta <amo@bakageta.com>
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
#include "hid_liber.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    led_init_ports();
    matrix_init_user();
}

void led_init_ports(void) {
    setPinOutput(B5);
    setPinOutput(B6);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B5, !led_state.caps_lock);
        writePin(B6, !led_state.scroll_lock);
    }
    return res;
}
