#include "display_func.h"

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
CST816S myTouch(4,0,32,33);


void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

void my_touch_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data) {
  //Creating the touch coordinator to store touch coordinate into data
  uint16_t touchX = 150;
  uint16_t touchY = 150;
  if (myTouch.available()) {
    touchX = myTouch.data.x;
    touchY = myTouch.data.y;
    data -> state = LV_INDEV_STATE_PR;
  }
  else {
    data -> state = LV_INDEV_STATE_REL;
  }
  data -> point.x = touchX;
  data -> point.y = touchY;
  }