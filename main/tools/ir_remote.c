#include "ir_remote.h"

#include <stddef.h>
#include <string.h>

#include "ir_receiver.h"
#include "ir_transmitter.h"

#define IR_REMOTE_MAX_SYMBOLS 256

static rmt_symbol_word_t learned_symbols[IR_REMOTE_MAX_SYMBOLS];
static size_t learned_num_symbols = 0;
static bool learning = false;

esp_err_t ir_remote_init(void) {

  esp_err_t error = receiver_init();

  if (error != ESP_OK) {
    return error;
  }

  return transmitter_init();
}

esp_err_t ir_remote_learn(void) {

  if (learning) {
    return ESP_ERR_INVALID_STATE;
  }

  esp_err_t error = receiver_start();

  if (error != ESP_OK) {
    return error;
  }

  learning = true;

  return ESP_OK;
}

bool ir_remote_poll(void) {

  if (!learning) {
    return false;
  }

  rmt_rx_done_event_data_t data;

  if (receiver_get_data(&data)) {
    learning = false;

    if (data.received_symbols == NULL || data.num_symbols == 0 ||
        data.num_symbols > IR_REMOTE_MAX_SYMBOLS) {

      return false;
    }
    memcpy(learned_symbols, data.received_symbols,
           sizeof(rmt_symbol_word_t) * data.num_symbols);

    learned_num_symbols = data.num_symbols;

    printf("Learned %zu symbols.\n", learned_num_symbols);

for (size_t i = 0; i < learned_num_symbols; i++) {

  printf("[%zu] L0: %u D0: %u | L1: %u D1: %u\n",
         i,
         (unsigned)learned_symbols[i].level0,
         (unsigned)learned_symbols[i].duration0,
         (unsigned)learned_symbols[i].level1,
         (unsigned)learned_symbols[i].duration1);
}

    return true;
  }

  return false;
}

bool ir_remote_has_command(){
    return learned_num_symbols > 0;
}

esp_err_t ir_remote_send(void) {

    if (!ir_remote_has_command() || learning){
        return ESP_ERR_INVALID_STATE;
    }

    return transmitter_send(learned_symbols, learned_num_symbols);

}