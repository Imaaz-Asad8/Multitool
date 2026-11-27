#ifndef IR_TRANSMITTER_H    
#define IR_TRANSMITTER_H

#include "esp_err.h"
#include "driver/rmt_types.h"

esp_err_t transmitter_init(void);
esp_err_t transmitter_send(const rmt_symbol_word_t *symbols, size_t num_symbols);

#endif 