#include "clock_trck.h"

struct buff_alarm buff_alarm1;
struct buff_alarm buff_countBack;
struct countDown_stct countDown_val;

lv_obj_t * list;
bool flag_stop = false;
bool flag_Switch = false;

int hour1 = 0;
int min1 = 0;
int sec1 = 0;
int interval = 1000;
unsigned long previousMs = 0; 
char timing_update [9];
////////////////////Tracking time End/////////////////////////

//////////////////Alarm variable///////////////////////
#define MAX_STRING 10
#define STRING_LENGTH 20
char stringSet[MAX_STRING][STRING_LENGTH];
bool flag_call = false;
int stringCount = 0;
lv_obj_t * obj_a;

bool addString(char var[]) {
  for (int ind = 0; ind < stringCount; ind++) {
    if (stringCount > MAX_STRING || strcmp(stringSet[ind], var) == 0) {
      return false;
    }
  }
  strcpy(stringSet[stringCount++],var);
  return true;
}

void deleteString (const char val[]) {
  int ind;
  for (ind = 0; ind < stringCount; ind++) {
    if (strcmp(stringSet[ind], val) == 0) {
      break;
    }
  }
  for (int ind_e = ind; ind_e < stringCount - 1; ind_e++) {
    strcpy(stringSet[ind_e], stringSet[ind_e + 1]);
  }
  stringCount--;
}

void printString() {
  Serial.printf("-------------------------\n");
  for (int ind = 0; ind < stringCount; ind++) {
    Serial.printf("%s\n",stringSet[ind]);
  }
  Serial.printf("-------------------------\n");
}
//////////////////////////String function end/////////////////////////////////////

////////////////////////////Wifi Function ////////////////////////////////////////
// void update_time_label() {
//   char time_str[6];
//   char date_str[10];
//   struct tm timeinfo;
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("No time available (yet)");
//     return;
//   }
//   strftime(time_str, sizeof(time_str), "%H\n%M", &timeinfo);
//   strftime(date_str, sizeof(date_str), "%b %d %y", &timeinfo);
//   strftime(timetrk, sizeof(date_str), "%a:%H:%M", &timeinfo);

  
//   lv_label_set_text(ui_Label1, time_str);
//   lv_label_set_text(ui_Label2, date_str);
// }

void setup_timer() {
    // Set up a timer to call update_time_label every sec1ond
    lv_timer_t * timer = lv_timer_create((lv_timer_cb_t) update_time_label, 1000, NULL);
    lv_timer_t *timer_stop = lv_timer_create((lv_timer_cb_t) stopWatch, 1000, NULL);
    lv_timer_t *timer_count = lv_timer_create((lv_timer_cb_t) countDown, 1000, NULL);
    
    
}
//////////////////////////Wifi Function END //////////////////////////////////////////

////////////////////////Stop Watch function /////////////////////////////////////////
void stopWatch () {
  if (!flag_stop || flag_Switch) {
    return;
  }
  unsigned long currentMs = millis();
  if (currentMs - previousMs >= interval) {
    sprintf(timing_update, "%02d:%02d:%02d", hour1, min1, sec1);
    lv_label_set_text(ui_Label13, timing_update);
    previousMs = currentMs;
    if (sec1 == 60) {
      sec1 = 0;
      min1++;
      if (min1 == 60) {
        hour1++;
      }
    }
    sec1++;
  }
}

void countDown () {
  if (!flag_stop || !flag_Switch) {
    return;
  }
  unsigned long currentMs = millis();
  if (currentMs - previousMs >= interval) {
    sprintf(timing_update, "%02d:%02d:%02d", countDown_val.d1, countDown_val.d2, countDown_val.d3);
    lv_label_set_text(ui_Label13, timing_update);
    previousMs = currentMs;
    if (countDown_val.d3 == 0) {
      countDown_val.d3 = 59;
      countDown_val.d2--;
      if (countDown_val.d2 == 0) {
        countDown_val.d2 = 59;
        countDown_val.d1--;
      }
    }
    countDown_val.d3--;
    if (countDown_val.d1 == 0 && countDown_val.d2 == 0 && countDown_val.d3 == 0) {
      flag_stop = false;
    }
  }

}

void event_handler_button8 (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = lv_event_get_target(e);
  if (code == LV_EVENT_PRESSED) {
    flag_stop = !flag_stop;
  }
}

void event_handler_button9 (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = lv_event_get_target(e);
  if (code == LV_EVENT_LONG_PRESSED) {
    lv_label_set_text(ui_Label13, "00:00:00");
    flag_stop = false;
    hour1 = 0;
    min1 = 0;
    sec1 = 0;


  }
}
//////////////////////////////Stop Watch function end/////////////////////////////////

/////////////////////////////Countdown start ////////////////////////////////
void event_handler_Button8_ON (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = lv_event_get_target(e);
  if (code == LV_EVENT_LONG_PRESSED) {
    _ui_screen_change(&ui_TabStop, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_TabStop_screen_init);
  } else if (code == LV_EVENT_PRESSED) {
    flag_stop = !flag_stop;
  }
}

void event_handler_Switch1 (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = lv_event_get_target(e);
  bool state = lv_obj_has_state(obj, LV_STATE_CHECKED);
  if (code == LV_EVENT_VALUE_CHANGED) {
    if (state) {
      //Switch to countdown
      flag_Switch = true;
      lv_obj_add_event_cb(ui_Button8, event_handler_Button8_ON, LV_EVENT_ALL, NULL);
      Serial.printf("Delete this bull shit\n");
      lv_obj_remove_event_cb (ui_Button8, event_handler_button8);
      
    }
    else {
      flag_Switch = false;
      lv_obj_add_event_cb(ui_Button8, event_handler_button8, LV_EVENT_ALL, NULL);
      Serial.printf("Delete this bull shit SWITCH OFF\n");
      lv_obj_remove_event_cb (ui_Button8, event_handler_Button8_ON);
    }
  }
  
}

////////////////////////Alarm function///////////////////////////////////////////////
//Creating the map


int lv_obj_t_Mapping (lv_event_code_t code_val,lv_obj_t* key) {
  
  if (code_val == LV_EVENT_VALUE_CHANGED) {
    if (key == ui_Roller6) {
      return 6;
    }
    else if (key == ui_Roller1) {
      return 1;
    }
    else if (key == ui_Roller2) {
      return 2;
    }
    else if (key == ui_Roller3) {
      return 3;
    }
    else if (key == ui_Roller4) {
      return 4;
    }
    else if (key == ui_Roller5) {
      return 5;
    }
    
  }
  return -1;
}
void event_handler_alarminfo (lv_event_t* e) {

  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  
  
  if(code == LV_EVENT_VALUE_CHANGED) {
    int val_select = lv_obj_t_Mapping(code,obj);
    Serial.printf("obj -> %d\n", val_select);
    switch (val_select){
      case 6:
        lv_roller_get_selected_str(obj, buff_alarm1.alarm1, sizeof(buff_alarm1.alarm1));
        break;
      case 1:
        lv_roller_get_selected_str(obj, buff_alarm1.alarm2, sizeof(buff_alarm1.alarm2));
        break;
      case 2:
        lv_roller_get_selected_str(obj, buff_alarm1.alarm3, sizeof(buff_alarm1.alarm3));
        break;
      case 3:
        lv_roller_get_selected_str(obj, buff_countBack.alarm3, sizeof(buff_countBack.alarm3));
        break;

      case 4:
        lv_roller_get_selected_str(obj, buff_countBack.alarm2, sizeof(buff_countBack.alarm2));
        break;
      case 5:
        lv_roller_get_selected_str(obj, buff_countBack.alarm1, sizeof(buff_countBack.alarm1));
        break;
      default:
        break;
    }
  }
}

static void event_handler_stopWatch(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * float_btn = lv_event_get_target(e);

    if(code == LV_EVENT_CLICKED) {
        char buff[9];
        buff[0] = '\0';
        strcat(buff, buff_countBack.alarm1);
        strcat(buff, ":");
        strcat(buff, buff_countBack.alarm2);
        strcat(buff, ":");
        strcat(buff, buff_countBack.alarm3);
        countDown_val.d1 = atoi(buff_countBack.alarm1);
        countDown_val.d2 = atoi(buff_countBack.alarm2);
        countDown_val.d3 = atoi(buff_countBack.alarm3);
        lv_label_set_text(ui_Label13,buff);

    }
}

void add_event_roller (void) {
  lv_obj_add_event_cb(ui_Roller6, event_handler_alarminfo, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Roller1, event_handler_alarminfo, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Roller2, event_handler_alarminfo, LV_EVENT_ALL, NULL);

  lv_obj_add_event_cb(ui_Roller3, event_handler_alarminfo, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Roller4, event_handler_alarminfo, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Roller5, event_handler_alarminfo, LV_EVENT_ALL, NULL);

  //Stopwatch
  lv_obj_add_event_cb(ui_Button8, event_handler_button8, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Button9, event_handler_button9, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Switch1, event_handler_Switch1, LV_EVENT_ALL, NULL);
  lv_obj_remove_event_cb(ui_Button8, ui_event_Button8);
}

static void delete_btn_event_cb (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_LONG_PRESSED) {
      const char* stringval = lv_list_get_btn_text(list, obj);
      deleteString(stringval);
      Serial.printf("%s\n",stringval);
      printString();
      lv_obj_del(obj);
    }
}


static void float_btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * float_btn = lv_event_get_target(e);
    bool list_e;

    if(code == LV_EVENT_CLICKED) {
        lv_obj_t * list = (lv_obj_t*) lv_event_get_user_data(e);
        char buff[30];
        buff[0] = '\0';
        strcat(buff, buff_alarm1.alarm3);
        strcat(buff, ":");
        strcat(buff, buff_alarm1.alarm2);
        strcat(buff, ":");
        strcat(buff, buff_alarm1.alarm1);
        //Final Adding is here
        list_e = addString(buff);
        printString();
        ///////////////////////
        if (list_e) {
          lv_obj_t * list_btn = lv_list_add_btn(list, LV_SYMBOL_LIST,buff);
          lv_obj_add_event_cb(list_btn, delete_btn_event_cb, LV_EVENT_ALL, NULL);
          lv_obj_move_foreground(float_btn);
          lv_obj_scroll_to_view(list_btn, LV_ANIM_ON);
        }

        if(strcmp(buff, timetrk)==0) {
          Serial.printf("True\n");
        } else{
          Serial.printf("Here is buff %s and timetrk %s\n", buff, timetrk);
        }   
    }
}


void listAlarmCountclock (void) {
  list = lv_list_create(ui_AlarmDisplay);
  lv_obj_set_size(list, 150, 60);
  lv_obj_set_pos(list,25,50);
  lv_obj_add_event_cb(ui_Addbttn,float_btn_event_cb,LV_EVENT_ALL, list);
  lv_obj_add_event_cb(ui_AddStopWatch,event_handler_stopWatch, LV_EVENT_ALL, NULL);
}

static void delete_btn_event_cb1 (lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_LONG_PRESSED) {
      lv_obj_del(obj);
    }
}

static void anim_x_cb(lv_obj_t * var, int32_t v)
{
    lv_obj_set_x(var, v);
}

static void anim_size_cb(lv_obj_t * var, int32_t v)
{
    lv_obj_set_size(var, v, v);
}

void ui_ringRingdelete (lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
    Serial.printf("Deleting already\n");
    lv_obj_del(obj_a);
  } 
}

void addingDelete (void) {
  lv_obj_add_event_cb(ui_ringRing,ui_ringRingdelete,LV_EVENT_ALL, NULL);  
}

void alarmCalloff(void) {
  if (flag_call) {
    return;
  }
  
  for (int ind = 0; ind < stringCount; ind++) {
    if (strcmp(stringSet[ind], timetrk) == 0) {
      flag_call = true;
      Serial.printf("Match\n");
    }
    // else {
    //   Serial.printf("Nooooooooooooooooooo\n");
    // }

    if (strcmp(stringSet[ind], timetrk) == 0) {
      Serial.printf("Yes im in\n");
      //This is the function start edit
      _ui_screen_change(&ui_ringRing, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ringRing_screen_init);
      obj_a = lv_obj_create(ui_ringRing);
      lv_obj_set_style_bg_color(obj_a, lv_palette_main(LV_PALETTE_RED), 0);
      lv_obj_set_style_radius(obj_a, LV_RADIUS_CIRCLE, 0);
      lv_obj_align(obj_a, LV_ALIGN_LEFT_MID, 10, 0);
      lv_obj_add_event_cb(obj_a,delete_btn_event_cb1,LV_EVENT_ALL, NULL);
      
      lv_anim_t a;
      lv_anim_init(&a);
      lv_anim_set_var(&a, obj_a);
      lv_anim_set_values(&a, 10, 50);
      lv_anim_set_time(&a, 1000);
      lv_anim_set_playback_delay(&a, 100);
      lv_anim_set_playback_time(&a, 300);
      lv_anim_set_repeat_delay(&a, 500);
      lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
      lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

      lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) anim_size_cb);
      lv_anim_start(&a);
      lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) anim_x_cb);
      lv_anim_set_values(&a, 10, 240);
      lv_anim_start(&a);
      break;
    }
  }
}