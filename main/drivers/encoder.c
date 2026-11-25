#include "driver/gpio.h"
#include "esp_err.h"
#include "hal/gpio_types.h"
#include "driver/pulse_cnt.h"
#include "hal/pcnt_types.h"
#include "esp_log.h"
#include "encoder.h"

#define CLK GPIO_NUM_1
#define DT GPIO_NUM_2
#define SW GPIO_NUM_3

static pcnt_unit_handle_t pcnt_unit = NULL;
static pcnt_channel_handle_t pcnt_chan = NULL;
static int last_count = 0;

void encoder_init(){

    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << SW,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    ESP_ERROR_CHECK(gpio_config(&io_conf));

    pcnt_unit_config_t unit_config = {
        .high_limit = 10000,
        .low_limit = -10000
    };

    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

    pcnt_chan_config_t chan_config = {
        .edge_gpio_num = CLK,
        .level_gpio_num = DT,
    };

    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_config, &pcnt_chan));

    ESP_ERROR_CHECK(gpio_set_pull_mode(DT, GPIO_PULLUP_ONLY));
    ESP_ERROR_CHECK(gpio_set_pull_mode(CLK, GPIO_PULLUP_ONLY));

    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_HOLD));

    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000
    };

    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config));

    ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));

    ESP_ERROR_CHECK(pcnt_unit_clear_count(pcnt_unit));

    last_count = 0;

    ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));
}

int encoder_read(){

    int counter = 0;

    ESP_ERROR_CHECK(pcnt_unit_get_count(pcnt_unit, &counter));

    int difference = counter - last_count;

   //ESP_LOGI("ENCODER", "Count: %d", difference);

    last_count = counter;

    return difference;

}

bool encoder_button_pressed(){

    
    bool pressed = gpio_get_level(SW);

    return (pressed == 0) ? 1 : 0;

}