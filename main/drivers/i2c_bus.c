#include "esp_err.h"
#include "i2c_bus.h"

#define SDA GPIO_NUM_5
#define SCL GPIO_NUM_6

static i2c_master_bus_handle_t bus_handle;

void i2c_bus_init(){

       i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = SCL,
        .sda_io_num = SDA,
        .glitch_ignore_cnt = 7
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));
}

i2c_master_bus_handle_t i2c_get_bus_handle(){
    return bus_handle;
}