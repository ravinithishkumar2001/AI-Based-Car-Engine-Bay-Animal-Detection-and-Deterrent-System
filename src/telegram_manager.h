#pragma once
#include <Arduino.h>
void initializeTelegram();
void telegramText(const String&);
void telegramPhoto(const String&,const String&);
void serviceTelegram();

