#include "ui_dmm.h"
#include "ui_styles.h"
#include "ui_common.h"
lv_group_t *dmm_group = NULL;

lv_obj_t *ui_dmm_screen(lv_event_cb_t back_callback) {

  dmm_group = lv_group_create();

  lv_obj_t *screen = lv_obj_create(NULL);
  ui_styles_apply_screen(screen);

  lv_obj_t *title = lv_label_create(screen);
  lv_label_set_text(title, "DMM");
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 2);

  ui_create_back_button(screen, dmm_group, back_callback);
  
  return screen;
}

lv_group_t *ui_dmm_group(void)
{
    return dmm_group;
}