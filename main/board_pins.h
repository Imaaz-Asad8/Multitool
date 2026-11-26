#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#include "driver/gpio.h"

#define ENCODER_CLK GPIO_NUM_4
#define ENCODER_DT GPIO_NUM_5
#define ENCODER_SW GPIO_NUM_6

#define I2C_SDA GPIO_NUM_15
#define I2C_SCL GPIO_NUM_16

#define SPI_MOSI   GPIO_NUM_11
#define SPI_SCLK    GPIO_NUM_12

#define TFT_CS     GPIO_NUM_10
#define TFT_RST     GPIO_NUM_13
#define TFT_DC      GPIO_NUM_14

#define IR_RX GPIO_NUM_21
#define IR_TX GPIO_NUM_47 

#endif