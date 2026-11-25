#include "st7789.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TFT_HOST SPI2_HOST

static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;

void st7789_init() {
  spi_bus_config_t bus_config = {.mosi_io_num = TFT_MOSI,
                                 .miso_io_num = -1,
                                 .sclk_io_num = TFT_SCLK,
                                 .quadhd_io_num = -1,
                                 .quadwp_io_num = -1,
                                 .max_transfer_sz =
                                     TFT_WIDTH * 80 * sizeof(uint16_t)};

  ESP_ERROR_CHECK(spi_bus_initialize(TFT_HOST, &bus_config, SPI_DMA_CH_AUTO));

  esp_lcd_panel_io_spi_config_t io_config = {.cs_gpio_num = TFT_CS,
                                             .dc_gpio_num = TFT_DC,
                                             .pclk_hz = TFT_FREQ,
                                             .spi_mode = 0,
                                             .lcd_cmd_bits = 8,
                                             .lcd_param_bits = 8,
                                             .trans_queue_depth = 10};

  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)TFT_HOST,
                                           &io_config, &io_handle));

  esp_lcd_panel_dev_config_t panel_config = {.bits_per_pixel = 16,
                                             .rgb_ele_order =
                                                 LCD_RGB_ELEMENT_ORDER_RGB,
                                             .reset_gpio_num = TFT_RST};

  ESP_ERROR_CHECK(
      esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

  ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));

  ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

  ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, 1));

  ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, 1));
}

esp_lcd_panel_io_handle_t st7789_get_io() { return io_handle; }

esp_lcd_panel_handle_t st7789_get_panel() { return panel_handle; }

void st7789_test(void) {

  static uint8_t buffer[TFT_WIDTH * 80 * 2];

  uint16_t colors[] = {0xF800, 0x07E0, 0x001F, 0xFFFF};

  for (int i = 0; i < 4; i++) {

    for (int j = 0; j < TFT_WIDTH * 80; j++) {
      buffer[j * 2] = colors[i] >> 8;
      buffer[j * 2 + 1] = colors[i] & 0xFF;
    }

    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 0, i * 80,
                                              TFT_WIDTH, (i + 1) * 80, buffer));

    vTaskDelay(pdMS_TO_TICKS(200));
  }
}