#include "motion_detector.h"
#include "camera_manager.h"
#include "config.h"
static uint8_t *refFrame=nullptr,*curFrame=nullptr;static bool haveRef=false;static uint32_t lastSample=0;
void initializeMotionDetection(){refFrame=(uint8_t*)ps_malloc(MOTION_WIDTH*MOTION_HEIGHT);curFrame=(uint8_t*)ps_malloc(MOTION_WIDTH*MOTION_HEIGHT);}
bool detectMotion(){if(!refFrame||!curFrame||millis()-lastSample<MOTION_INTERVAL_MS)return false;lastSample=millis();if(!captureMotionFrame(curFrame,MOTION_WIDTH*MOTION_HEIGHT))return false;if(!haveRef){memcpy(refFrame,curFrame,MOTION_WIDTH*MOTION_HEIGHT);haveRef=true;return false;}size_t changed=0;for(size_t i=0;i<MOTION_WIDTH*MOTION_HEIGHT;i+=2)if(abs((int)curFrame[i]-(int)refFrame[i])>=MOTION_DIFF_THRESHOLD)changed++;memcpy(refFrame,curFrame,MOTION_WIDTH*MOTION_HEIGHT);return changed*100/(MOTION_WIDTH*MOTION_HEIGHT/2)>=8;}
void updateReferenceFrame(){haveRef=false;}

