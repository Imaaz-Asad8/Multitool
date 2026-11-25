#ifndef UI_STYLES_H
#define UI_STYLES_H
#include "lvgl.h"

void ui_styles_init(void);
void ui_styles_apply_button(lv_obj_t *button);
void ui_styles_apply_screen(lv_obj_t *screen);
void ui_styles_apply_grid(lv_obj_t *grid);

#endif