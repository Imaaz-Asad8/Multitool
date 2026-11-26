#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <stdbool.h>

#include "esp_err.h"
#include "driver/rmt_rx.h"

esp_err_t receiver_init(void);
esp_err_t receiver_start(void);
bool receiver_get_data(rmt_rx_done_event_data_t *data);

#endif 

