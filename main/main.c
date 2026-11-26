#include <stdio.h>

#include "display.h"
#include "encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_bus.h"
#include "ir_receiver.h"
#include "st7789.h"
#include "ui.h"
#include "ui_input.h"

rmt_rx_done_event_data_t data;

void app_main(void) {
  /*
  i2c_bus_init();
  st7789_init();
  display_init();
  encoder_init();
  ui_input_init();
  ui_init();
  */

  receiver_init();
  receiver_start();

  while (1) {
    if (receiver_get_data(&data) == pdTRUE) {
      printf("Received: %zu\n", data.num_symbols);

      for (int i = 0; i < data.num_symbols; i++) {
        printf("[%zu] Level: %u, Duration: %u us | "
               "Level: %u, Duration: %u us\n",
               i, (unsigned)data.received_symbols[i].level0,
               (unsigned)data.received_symbols[i].duration0,
               (unsigned)data.received_symbols[i].level1,
               (unsigned)data.received_symbols[i].duration1);
      }

      receiver_start();
    }

    vTaskDelay(pdMS_TO_TICKS(20));
  }
}
