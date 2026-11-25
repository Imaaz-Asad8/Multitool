#include "ui_styles.h"

static lv_style_t button_style;
static lv_style_t focused_style;
static lv_style_t screen_style;
static lv_style_t grid_style;

void ui_styles_init() {
  lv_style_init(&button_style);
  lv_style_init(&focused_style);
  lv_style_init(&screen_style);
  lv_style_init(&grid_style);

  lv_style_set_bg_color(&button_style, lv_color_white());
  lv_style_set_text_color(&button_style, lv_color_black());
  lv_style_set_radius(&button_style, 4);
  lv_style_set_border_width(&button_style, 0);
  lv_style_set_width(&button_style, 54);
  lv_style_set_height(&button_style, 22);
  lv_style_set_bg_opa(&button_style, LV_OPA_COVER);

  lv_style_set_bg_color(&focused_style, lv_color_black());
  lv_style_set_text_color(&focused_style, lv_color_white());
  lv_style_set_border_width(&focused_style, 1);
  lv_style_set_border_color(&focused_style, lv_color_white());

  lv_style_set_bg_color(&screen_style, lv_color_black());
  lv_style_set_bg_opa(&screen_style, LV_OPA_COVER);
  lv_style_set_text_color(&screen_style, lv_color_white());

  lv_style_set_width(&grid_style, lv_pct(100));
  lv_style_set_height(&grid_style, lv_pct(100));
  lv_style_set_pad_all(&grid_style, 2);
  lv_style_set_pad_column(&grid_style, 2);
  lv_style_set_pad_row(&grid_style, 2);
  lv_style_set_border_width(&grid_style, 0);
  lv_style_set_bg_opa(&grid_style, LV_OPA_TRANSP);
}

void ui_styles_apply_button(lv_obj_t *button) {
  lv_obj_add_style(button, &button_style, 0);
  lv_obj_add_style(button, &focused_style, LV_STATE_FOCUSED);
}

void ui_styles_apply_screen(lv_obj_t *screen) {
  lv_obj_add_style(screen, &screen_style, 0);
}

void ui_styles_apply_grid(lv_obj_t *grid) {
    lv_obj_add_style(grid, &grid_style, 0);
}