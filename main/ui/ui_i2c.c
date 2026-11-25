#include "ui_i2c.h"

#include <stdint.h>

#include "i2c_bus.h"
#include "i2c_scanner.h"
#include "ui_common.h"
#include "ui_styles.h"

static lv_group_t *i2c_group = NULL;
static lv_obj_t *results_label = NULL;

static void scan_click_cb(lv_event_t *event) {
  uint8_t addresses[112];

  int count = scanner(i2c_get_bus_handle(), addresses);

  if (count == 0) {
    lv_label_set_text(results_label, "No devices");
  } else {
    lv_label_set_text_fmt(results_label, "Found: 0x%02X", addresses[0]);
  }
}

lv_obj_t *ui_i2c_screen(lv_event_cb_t back_callback) {
  i2c_group = lv_group_create();

  lv_obj_t *screen = lv_obj_create(NULL);
  ui_styles_apply_screen(screen);

  ui_create_title(screen, "I2C Scanner");

  results_label = lv_label_create(screen);
  lv_obj_align(results_label, LV_ALIGN_TOP_MID, 0, 19);

  lv_obj_t *scan_button =
      ui_create_button(screen, "Scan", i2c_group, scan_click_cb);

  lv_obj_align(scan_button, LV_ALIGN_BOTTOM_LEFT, 0, -2);

  lv_obj_t *back_button =
      ui_create_back_button(screen, i2c_group, back_callback);

  lv_obj_align(back_button, LV_ALIGN_BOTTOM_RIGHT, -4, -2);

  return screen;
}

lv_group_t *ui_i2c_group(void) { return i2c_group; }

void ui_i2c_reset(){
  if (results_label != NULL){
    lv_label_set_text(results_label, "Ready to scan");
  }
}