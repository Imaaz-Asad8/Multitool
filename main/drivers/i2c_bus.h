#ifndef I2C_BUS_H
#define I2C_BUS_H

#include "driver/i2c_master.h"


void i2c_bus_init();

i2c_master_bus_handle_t i2c_get_bus_handle();

#endif