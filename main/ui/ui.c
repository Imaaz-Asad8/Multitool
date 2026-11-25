#include "ui.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "ui_common.h"
#include "ui_dmm.h"
#include "ui_input.h"
#include "ui_styles.h"
#include "ui_i2c.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
  const char *text;
  lv_event_cb_t callback;
} menu_item_t;

static lv_obj_t *main_menu_screen = NULL;
static lv_obj_t *dmm_screen = NULL;
static lv_obj_t *i2c_screen = NULL;

static int32_t columns[3] = {LV_GRID_FR(1), LV_GRID_FR(1),
                             LV_GRID_TEMPLATE_LAST};
static int32_t rows[3] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

static void back_click_cb(lv_event_t *event) {
  ui_input_set_group(ui_input_group());
  lv_screen_load(main_menu_screen);
}

static void dmm_click_cb(lv_event_t *event) {

  if (dmm_screen == NULL) {
    dmm_screen = ui_dmm_screen(back_click_cb);
  }

  ui_input_set_group(ui_dmm_group());
  lv_screen_load(dmm_screen);
}

static void i2c_click_cb(lv_event_t *event) {

    if (i2c_screen == NULL) {
        i2c_screen = ui_i2c_screen(back_click_cb);
    }

    ui_input_set_group(ui_i2c_group());
    lv_screen_load(i2c_screen);
}

static menu_item_t items[] = {
    {"DMM", dmm_click_cb}, {"IR", NULL}, {"I2C", i2c_click_cb}, {"Gen", NULL}};

void ui_init() {
  if (lvgl_port_lock(0)) {

    ui_styles_init();

    lv_group_t *main_group = ui_input_group();

    lv_obj_t *screen = lv_screen_active();
    ui_styles_apply_screen(screen);

    main_menu_screen = screen;

    lv_obj_t *menu = ui_create_grid(screen, columns, rows);

    size_t count = sizeof(items) / sizeof(items[0]);

    for (size_t i = 0; i < count; i++) {

      lv_obj_t *button =
          ui_create_button(menu, items[i].text, main_group, items[i].callback);

      ui_grid_place(button, i % 2, i / 2, 1, 1);
    }

    lvgl_port_unlock();
  }
}
