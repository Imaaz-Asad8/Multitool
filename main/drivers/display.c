#include "display.h"

#include <assert.h>

#include "esp_err.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#include "st7789.h"

#define DISPLAY_BUFFER_ROWS 80

void display_init() {
  const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();

  ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

  const lvgl_port_display_cfg_t disp_cfg = {
      .buffer_size = TFT_WIDTH * DISPLAY_BUFFER_ROWS,
      .io_handle = st7789_get_io(),
      .panel_handle = st7789_get_panel(),
      .hres = TFT_WIDTH,
      .vres = TFT_HEIGHT,
      .monochrome = false,
      .color_format = LV_COLOR_FORMAT_RGB565,
      .rotation = {.mirror_x = false, .mirror_y = false, .swap_xy = false},
      .flags = {.swap_bytes = true, .sw_rotate = false, .buff_dma = true},
  };

  lv_display_t *disp_handle = lvgl_port_add_disp(&disp_cfg);

  assert(disp_handle != NULL);
}
