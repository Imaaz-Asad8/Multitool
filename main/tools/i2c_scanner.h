#ifndef I2C_SCANNER_H
#define I2C_SCANNER_H

#include "driver/i2c_master.h"

int scanner(i2c_master_bus_handle_t bus, uint8_t *addresses);

#endif 