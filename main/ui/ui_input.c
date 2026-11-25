#include "ui_input.h"
#include "encoder.h"
#include "include/lvgl/core/lv_group.h"
#include "include/lvgl/indev/lv_indev.h"
#include "include/lvgl/lv_types.h"

static lv_group_t *group = NULL;
static lv_indev_t *indev = NULL;

static void encoder_read_cb(lv_indev_t *indev, lv_indev_data_t *data){
    data->enc_diff = encoder_read();
    data->state = encoder_button_pressed() ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

void ui_input_init() {
     indev = lv_indev_create();

    lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);

    lv_indev_set_read_cb(indev, encoder_read_cb);

    group = lv_group_create();

    lv_indev_set_group(indev, group);

}

lv_group_t *ui_input_group(){
    return group;
}

void ui_input_set_group(lv_group_t *group){
    lv_indev_set_group(indev, group);
}