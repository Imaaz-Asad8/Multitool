#include "display.h"
#include "i2c_bus.h"
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

  i2c_bus_init();
  st7789_init();
  display_init();
  encoder_init();
  ui_input_init();
  ui_init();
}
