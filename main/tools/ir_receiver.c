#include "ir_receiver.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "board_pins.h"

#define IR_RX_RESOLUTION 1000000
#define IR_RX_MEM_SYMBOLS 48
#define IR_RX_BUFFER_SYMBOLS 256

static rmt_symbol_word_t rx_buffer[IR_RX_BUFFER_SYMBOLS];
static rmt_channel_handle_t rx_channel = NULL;
static QueueHandle_t rx_queue = NULL;

static const rmt_receive_config_t receive_config = {
    .signal_range_min_ns = 1000,
    .signal_range_max_ns = 12000000,
};

static bool rx_done_callback(rmt_channel_handle_t channel,
                             const rmt_rx_done_event_data_t *event_data,
                             void *user_ctx) {

  BaseType_t awake = pdFALSE;

  xQueueSendFromISR(rx_queue, event_data, &awake);

  return (awake == pdTRUE);
}

esp_err_t receiver_init(void) {

  rx_queue = xQueueCreate(1, sizeof(rmt_rx_done_event_data_t));

  if (rx_queue == NULL) {
    return ESP_ERR_NO_MEM;
  }

  rmt_rx_channel_config_t rx_config = {.clk_src = RMT_CLK_SRC_DEFAULT,
                                       .gpio_num = IR_RX,
                                       .resolution_hz = IR_RX_RESOLUTION,
                                       .mem_block_symbols = IR_RX_MEM_SYMBOLS};

  ESP_ERROR_CHECK(rmt_new_rx_channel(&rx_config, &rx_channel));

  rmt_rx_event_callbacks_t callbacks = {.on_recv_done = rx_done_callback};

  ESP_ERROR_CHECK(
      rmt_rx_register_event_callbacks(rx_channel, &callbacks, NULL));

  ESP_ERROR_CHECK(rmt_enable(rx_channel));

  return ESP_OK;
}

esp_err_t receiver_start(void) {
  return rmt_receive(rx_channel, rx_buffer, sizeof(rx_buffer), &receive_config);
}

bool receiver_get_data(rmt_rx_done_event_data_t *data){

    return(xQueueReceive(rx_queue, data, 0) == pdTRUE);
}


