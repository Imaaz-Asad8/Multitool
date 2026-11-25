#ifndef ST7789_H
#define ST7789_H  

#include "esp_lcd_types.h"

#define TFT_HEIGHT 320
#define TFT_WIDTH 240

void st7789_init(void);

esp_lcd_panel_io_handle_t st7789_get_io(void);
esp_lcd_panel_handle_t st7789_get_panel(void);
void st7789_test(void);

#endif