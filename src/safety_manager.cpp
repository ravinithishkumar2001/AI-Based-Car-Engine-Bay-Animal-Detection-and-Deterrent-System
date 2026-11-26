#include "safety_manager.h"
#include "config.h"
void initializeSafety(){pinMode(ULTRASONIC_ENABLE_GPIO,OUTPUT);digitalWrite(ULTRASONIC_ENABLE_GPIO,LOW);}
bool safetyAllowsActuation(){return true;}
void serviceSafety(){}

