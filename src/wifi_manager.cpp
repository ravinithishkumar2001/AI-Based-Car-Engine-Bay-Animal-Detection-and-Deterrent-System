#include "wifi_manager.h"
#include <WiFi.h>
#include <time.h>
#include "../include/secrets.h"
void initializeWiFi(){WiFi.mode(WIFI_STA);WiFi.begin(WIFI_SSID,WIFI_PASSWORD);}
void serviceWiFi(){static uint32_t retry=0;static bool clockRequested=false;if(WiFi.status()!=WL_CONNECTED){clockRequested=false;if(millis()-retry>15000){retry=millis();WiFi.disconnect();WiFi.begin(WIFI_SSID,WIFI_PASSWORD);}}else if(!clockRequested){configTime(0,0,"pool.ntp.org","time.nist.gov");clockRequested=true;}}
bool wifiReady(){return WiFi.status()==WL_CONNECTED;}
bool syncClock(){if(!wifiReady())return false;configTime(0,0,"pool.ntp.org","time.nist.gov");struct tm t{};return getLocalTime(&t,5000);}

