#ifndef WIRELESS_CONNECT_H
#define WIRELESS_CONNECT_H

#include <time.h>
#include "esp_sntp.h"
#include "ui.h"
#include <Arduino.h>

//Wifi Initialization
extern char timetrk[13];
extern const char* ssid;
extern const char* password;
extern const char* ntpServer1;
extern const char* ntpServer2;
extern const long  gmtOffset_sec1;
extern const int   daylightOffset_sec1;
extern const char* time_zone;  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

void update_time_label();

#endif

