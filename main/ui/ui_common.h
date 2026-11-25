#ifndef UI_COMMON_H
#define UI_COMMON_H

#include "lvgl.h"

lv_obj_t *ui_create_button(lv_obj_t *parent, const char *text, lv_group_t *group, lv_event_cb_t callback);
lv_obj_t *ui_create_back_button(lv_obj_t *parent, lv_group_t *group, lv_event_cb_t callback);
lv_obj_t *ui_create_grid(lv_obj_t *parent, const int32_t *columns, const int32_t *rows);
void ui_grid_place(lv_obj_t *obj, int32_t column, int32_t row, int32_t col_span, int32_t row_span);
#endif