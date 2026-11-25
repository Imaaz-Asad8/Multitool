#ifndef UI_I2C_H
#define UI_I2C_H

#include "lvgl.h"

lv_obj_t *ui_i2c_screen(lv_event_cb_t back_callback);
lv_group_t *ui_i2c_group(void);
void ui_i2c_reset(void);

#endif
