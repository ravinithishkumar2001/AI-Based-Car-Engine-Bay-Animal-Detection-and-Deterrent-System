#include "telegram_manager.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <SD_MMC.h>
#include "wifi_manager.h"
#include "../include/secrets.h"
static WiFiClientSecure client;static UniversalTelegramBot*bot=nullptr;static File uploadFile;
static bool photoMoreData(){return uploadFile&&uploadFile.available();}
static byte photoByte(){return uploadFile?(byte)uploadFile.read():0;}
void initializeTelegram(){client.setCACert(TELEGRAM_CERTIFICATE_ROOT);bot=new UniversalTelegramBot(TELEGRAM_BOT_TOKEN,client);}
void telegramText(const String&m){if(bot&&wifiReady())bot->sendMessage(TELEGRAM_CHAT_ID,m,"");}
void telegramPhoto(const String&path,const String&caption){if(!bot||!wifiReady())return;uploadFile=SD_MMC.open(path);if(!uploadFile)return;bot->sendPhotoByBinary(TELEGRAM_CHAT_ID,"image/jpeg",(int)uploadFile.size(),photoMoreData,photoByte,nullptr,nullptr);uploadFile.close();if(caption.length())telegramText(caption);}
void serviceTelegram(){}

