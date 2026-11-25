#include "display.h"
#include "driver/gpio.h"
#include "encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_scanner.h"
#include "ui.h"
#include "ui_input.h"
#include "st7789.h"
#include <stdio.h>

void app_main(void) {
/*
  oled_init();

  
  oled_lvgl_init();
  encoder_init();
  ui_input_init();
  ui_init();

  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  
  */

  st7789_init();
  st7789_test();
}
