#ifndef ST7789_H
#define ST7789_H  

#include "driver/gpio.h"
#include "esp_lcd_types.h"

#define TFT_HEIGHT 320
#define TFT_WIDTH 240

#define TFT_MOSI GPIO_NUM_9
#define TFT_SCLK GPIO_NUM_7
#define TFT_CS   GPIO_NUM_8
#define TFT_DC   GPIO_NUM_44
#define TFT_RST  GPIO_NUM_4
#define TFT_FREQ 20000000

void st7789_init(void);

esp_lcd_panel_io_handle_t st7789_get_io(void);
esp_lcd_panel_handle_t st7789_get_panel(void);
void st7789_test(void);

#endif