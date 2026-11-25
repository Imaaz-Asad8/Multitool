#include "ui_dmm.h"
#include "ui_styles.h"
#include "ui_common.h"

static lv_group_t *dmm_group = NULL;

lv_obj_t *ui_dmm_screen(lv_event_cb_t back_callback) {

  dmm_group = lv_group_create();

  lv_obj_t *screen = lv_obj_create(NULL);
  ui_styles_apply_screen(screen);

  ui_create_title(screen, "DMM");

  ui_create_back_button(screen, dmm_group, back_callback);
  
  return screen;
}

lv_group_t *ui_dmm_group(void)
{
    return dmm_group;
}