#include <stdio.h>

#include "display.h"
#include "encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_bus.h"
#include "st7789.h"
#include "ui.h"
#include "ui_input.h"
#include "ir_remote.h"

void app_main(void) {
  /*
  i2c_bus_init();
  st7789_init();
  display_init();
  encoder_init();
  ui_input_init();
  ui_init();
  */

  ESP_ERROR_CHECK(ir_remote_init());

  ESP_ERROR_CHECK(ir_remote_learn());

  printf("Waiting for command.\n");

  while (!ir_remote_poll()){
    vTaskDelay(pdMS_TO_TICKS(20));
  }

  printf("Command learned.\n");


  while (1){
  
  vTaskDelay(pdMS_TO_TICKS(2000));
  printf("Transmitting.\n");
  ESP_ERROR_CHECK(ir_remote_send());
  printf("Transmission complete.\n");
  }
}
