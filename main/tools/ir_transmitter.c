#include "ir_transmitter.h"

#include "driver/rmt_tx.h"


#include "board_pins.h"

#define IR_TX_RESOLUTION 1000000
#define IR_TX_MEM_SYMBOLS 48
#define IR_TX_CARRIER_WAVE 38000
#define IR_TX_buffer_SYMBOLS 256

static rmt_channel_handle_t tx_channel = NULL;
static rmt_encoder_handle_t tx_encoder = NULL;
static rmt_symbol_word_t tx_buffer[IR_TX_buffer_SYMBOLS];

static const rmt_transmit_config_t transmit_config = {
    .loop_count = 0,
    .flags.eot_level = 0,
};

esp_err_t transmitter_init(void){

    rmt_tx_channel_config_t tx_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .gpio_num = IR_TX,
        .mem_block_symbols = IR_TX_MEM_SYMBOLS,
        .resolution_hz = IR_TX_RESOLUTION,
        .trans_queue_depth = 1
    };

    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_config, &tx_channel));
    
    rmt_carrier_config_t carrier_config = {
        .duty_cycle = 0.33f,
        .frequency_hz = IR_TX_CARRIER_WAVE,
        .flags.polarity_active_low = false
    };
    
    ESP_ERROR_CHECK(rmt_apply_carrier(tx_channel, &carrier_config));
    
    rmt_copy_encoder_config_t encoder_config = {};
    
    ESP_ERROR_CHECK(rmt_new_copy_encoder(&encoder_config, &tx_encoder));

    ESP_ERROR_CHECK(rmt_enable(tx_channel));

    return ESP_OK;

}

esp_err_t transmitter_send(const rmt_symbol_word_t *symbols, size_t num_symbols){

    if (symbols == NULL || num_symbols == 0 || num_symbols > IR_TX_buffer_SYMBOLS){
        return ESP_ERR_INVALID_ARG;
    }

    for (size_t i = 0; i < num_symbols; i++){
        tx_buffer[i] = symbols[i];

        tx_buffer[i].level0 = !tx_buffer[i].level0;
        tx_buffer[i].level1 = !tx_buffer[i].level1;

    }

    size_t payload = num_symbols * sizeof(rmt_symbol_word_t);

    esp_err_t error = rmt_transmit(tx_channel, tx_encoder, tx_buffer, payload, &transmit_config);

    if (error != ESP_OK){
        return error;
    }

    return rmt_tx_wait_all_done(tx_channel, -1);
}