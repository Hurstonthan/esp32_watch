// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_ringRing_screen_init(void)
{
    ui_ringRing = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ringRing, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ringRing, lv_color_hex(0xFAF7FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ringRing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ringRing, ui_event_ringRing, LV_EVENT_ALL, NULL);

}