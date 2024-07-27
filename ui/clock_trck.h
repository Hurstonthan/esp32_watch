#ifndef CLOCK_TRCK_H
#define CLOCK_TRCK_H

#define MAX_STRING 10
#define STRING_LENGTH 20

#include <lvgl.h>
#include "wireless_connect.h"
#include <ui.h>
#include <Arduino.h>


typedef struct buff_alarm {
  char alarm1[05];
  char alarm2[05];
  char alarm3[05];
  
} buff_alarm;

typedef struct countDown_stct {
  int d1 = 0;
  int d2 = 0;
  int d3 = 0;
} countDown_stct;

extern struct buff_alarm buff_alarm1;
extern struct buff_alarm buff_countBack;
extern struct countDown_stct countDown_val;

extern lv_obj_t * list;
extern bool flag_stop;
extern bool flag_Switch;

extern int hour1;
extern int min1;
extern int sec1;
extern int interval;
extern unsigned long previousMs; 
extern char timing_update [9];
////////////////////Tracking time End/////////////////////////

//////////////////Alarm variable///////////////////////
extern char stringSet[MAX_STRING][STRING_LENGTH];
extern bool flag_call;
extern int stringCount;
extern lv_obj_t * obj_a;

bool addString(char var[]);
void deleteString (const char val[]);
void printString();
void setup_timer();

//Stop Watch function
void stopWatch();
void countDown();

void event_handler_button8 (lv_event_t *e);
void event_handler_button9 (lv_event_t *e);
//////////////////////////////Stop Watch function end/////////////////////////////////

/////////////////////////////Countdown start ////////////////////////////////
void event_handler_Button8_ON (lv_event_t *e);
void event_handler_Switch1 (lv_event_t *e);
int lv_obj_t_Mapping (lv_event_code_t code_val,lv_obj_t* key);
void event_handler_alarminfo (lv_event_t* e); 
static void event_handler_stopWatch(lv_event_t * e);
void add_event_roller (void);
static void delete_btn_event_cb (lv_event_t *e);
static void float_btn_event_cb(lv_event_t * e);
void listAlarmCountclock (void);
static void delete_btn_event_cb1 (lv_event_t *e);
static void anim_x_cb(lv_obj_t * var, int32_t v);
static void anim_size_cb(lv_obj_t * var, int32_t v);
void ui_ringRingdelete (lv_event_t *e);
void addingDelete (void);
void alarmCalloff(void);





#endif