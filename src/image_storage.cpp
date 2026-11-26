#include "image_storage.h"
#include "config.h"
#include <SD_MMC.h>
#include <time.h>
bool initializeImageStorage(){if(!SD_MMC.setPins(SD_CLK,SD_CMD,SD_D0)||!SD_MMC.begin("/sdcard",true,false))return false;SD_MMC.mkdir("/animal_monitor");SD_MMC.mkdir("/animal_monitor/photos");SD_MMC.mkdir("/animal_monitor/logs");return true;}
String savePhoto(const uint8_t*d,size_t n,const char*phase,AnimalClass l,float c){char p[128];struct tm t{};if(getLocalTime(&t,10))snprintf(p,sizeof(p),"/animal_monitor/photos/%04d%02d%02d_%02d%02d%02d_%s_%s.jpg",t.tm_year+1900,t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec,phase,animalClassName(l));else snprintf(p,sizeof(p),"/animal_monitor/photos/unsynced_%lu_%s_%s.jpg",millis(),phase,animalClassName(l));File f=SD_MMC.open(p,FILE_WRITE);if(!f)return String();f.write(d,n);f.close();char x[96];snprintf(x,sizeof(x),"%s,%.3f,%s",animalClassName(l),c,p);logEvent(phase,x);return String(p);}
void logEvent(const char*e,const char*d){File f=SD_MMC.open("/animal_monitor/logs/detection_log.csv",FILE_APPEND);if(f){f.printf("%lu,%s,%s\n",millis(),e,d?d:"");f.close();}}
void manageStorage(){if(!SD_MMC.totalBytes()||SD_MMC.usedBytes()*100/SD_MMC.totalBytes()<=90)return;File dir=SD_MMC.open("/animal_monitor/photos");String oldest;while(dir){File f=dir.openNextFile();if(!f)break;if(!f.isDirectory()&&(oldest.isEmpty()||String(f.name())<oldest))oldest=f.name();f.close();}dir.close();if(!oldest.isEmpty()){SD_MMC.remove(oldest);logEvent("STORAGE_DELETE_OLDEST",oldest.c_str());}}

