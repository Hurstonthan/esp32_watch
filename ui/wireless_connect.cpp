#include "wireless_connect.h"


char timetrk[13];
const char* ssid       = "ID";
const char* password   = "password";
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec1 = -18000;
const int   daylightOffset_sec1 = 3600;
const char* time_zone = "EST5EDT,M3.2.0,M11.1.0";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

void update_time_label() {
  char time_str[6];
  char date_str[10];
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  strftime(time_str, sizeof(time_str), "%H\n%M", &timeinfo);
  strftime(date_str, sizeof(date_str), "%b %d %y", &timeinfo);
  strftime(timetrk, sizeof(date_str), "%a:%H:%M", &timeinfo);

  
  lv_label_set_text(ui_Label1, time_str);
  lv_label_set_text(ui_Label2, date_str);
}

