#ifndef DISPLAY_H
#define DISPLAY_H

#include "driver/i2c_master.h"

void oled_init();
void oled_test();
void oled_clear();
void oled_lvgl_init();
i2c_master_bus_handle_t oled_get_bus(void);

#endif