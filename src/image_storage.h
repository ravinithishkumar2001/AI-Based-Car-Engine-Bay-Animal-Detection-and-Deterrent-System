#pragma once
#include <Arduino.h>
#include "animal_classifier.h"
bool initializeImageStorage();
String savePhoto(const uint8_t*,size_t,const char*,AnimalClass,float);
void logEvent(const char*,const char*);
void manageStorage();

