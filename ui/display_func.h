#ifndef DISPLAY_FUNC_H
#define DISPLAY_FUNC_H
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <CST816S.h>
#include <Arduino.h>




extern TFT_eSPI tft; 
extern CST816S myTouch;
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void my_touch_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data);

#endif