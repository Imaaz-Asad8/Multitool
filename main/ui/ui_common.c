#include "ui_common.h"

#include "ui_styles.h"

lv_obj_t *ui_create_button(lv_obj_t *parent, const char *text,
                           lv_group_t *group, lv_event_cb_t callback) {

  lv_obj_t *button = lv_button_create(parent);

  ui_styles_apply_button(button);

  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_center(label);

  if (group != NULL) {
    lv_group_add_obj(group, button);
  }

  if (callback != NULL) {
    lv_obj_add_event_cb(button, callback, LV_EVENT_CLICKED, NULL);
  }

  return button;
}

lv_obj_t *ui_create_back_button(lv_obj_t *parent, lv_group_t *group,
                                lv_event_cb_t callback) {
  lv_obj_t *button = ui_create_button(parent, "Back", group, callback);

    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -2);

    return button;
}

lv_obj_t *ui_create_grid(lv_obj_t *parent, const int32_t *columns,
                         const int32_t *rows) {

  lv_obj_t *grid = lv_obj_create(parent);

  ui_styles_apply_grid(grid);

  lv_obj_set_pos(grid, 0, 0);
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(grid, columns, rows);

  return grid;
}

void ui_grid_place(lv_obj_t *obj, int32_t column, int32_t row, int32_t col_span,
                   int32_t row_span) {

  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, column, col_span,
                       LV_GRID_ALIGN_STRETCH, row, row_span);
}

lv_obj_t *ui_create_title(lv_obj_t *parent,
                          const char *text) {

    lv_obj_t *title = lv_label_create(parent);

    lv_label_set_text(title, text);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 2);

    return title;
}