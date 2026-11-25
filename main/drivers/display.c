#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "driver/i2c_types.h"
#include "esp_err.h"
#include "esp_lcd_io_i2c.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_ssd1306.h"
#include "esp_lcd_types.h"
#include "esp_lvgl_port_disp.h"
#include "hal/i2c_types.h"
#include "include/lvgl/draw/lv_color.h"
#include "soc/clk_tree_defs.h"
#include "display.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "assert.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"


#define SDA GPIO_NUM_5
#define SCL GPIO_NUM_6

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C

static i2c_master_bus_handle_t bus_handle;
static esp_lcd_panel_io_handle_t io_handle;
static esp_lcd_panel_handle_t panel_handle;
static lv_display_t *disp_handle;

void oled_init(){
    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = SCL,
        .sda_io_num = SDA,
        .glitch_ignore_cnt = 7
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = OLED_ADDR,
        .scl_speed_hz = 400000,
        .control_phase_bytes = 1,
        .dc_bit_offset = 6,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8
    };

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(bus_handle, &io_config, &io_handle));

    esp_lcd_panel_ssd1306_config_t ssd_config = {
      .height = OLED_HEIGHT
    };

    esp_lcd_panel_dev_config_t panel_config = {
        .bits_per_pixel = 1,
        .reset_gpio_num = -1,
        .vendor_config = &ssd_config
    };

    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle));

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));

    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, 1, 1));

    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, 1));

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, 1));
}

void oled_lvgl_init(){
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();

    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    const lvgl_port_display_cfg_t disp_cfg = {
        .buffer_size = OLED_HEIGHT * OLED_WIDTH,
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .hres = OLED_WIDTH,
        .vres = OLED_HEIGHT,
        .monochrome = true,
        .color_format = LV_COLOR_FORMAT_RGB565,
        .rotation = {
            .mirror_x = true,
            .mirror_y = true,
            .swap_xy = false
        },
        .flags = {
          .swap_bytes = false,
          .sw_rotate = false  
        },
    };

    disp_handle = lvgl_port_add_disp(&disp_cfg);

    assert(disp_handle != NULL);
}

void oled_clear(){

    static uint8_t blank[OLED_WIDTH * OLED_HEIGHT / 8] = {0};

    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(
        panel_handle,
        0, 0,
        OLED_WIDTH, OLED_HEIGHT,
        blank
    ));
}

void oled_test(){

    static uint8_t hello[] = {
        0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, // H
        0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, // E
        0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, // L
        0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, // L
        0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00  // O
    };

    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(
        panel_handle,
        0, 0,
        30, 8,
        hello
    ));
}

i2c_master_bus_handle_t oled_get_bus(void) {
    return bus_handle;
}



