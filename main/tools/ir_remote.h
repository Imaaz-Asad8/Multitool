#ifndef IR_REMOTE_H
#define IR_REMOTE_H

#include "esp_err.h"
#include <stdbool.h>

esp_err_t ir_remote_init(void);
esp_err_t ir_remote_learn(void);
bool ir_remote_poll(void);
esp_err_t ir_remote_send(void);
bool ir_remote_has_command(void);

#endif