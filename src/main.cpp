#include <Arduino.h>
#include "config.h"
#include "camera_manager.h"
#include "motion_detector.h"
#include "animal_classifier.h"
#include "image_storage.h"
#include "wifi_manager.h"
#include "telegram_manager.h"
#include "deterrent_controller.h"
#include "safety_manager.h"
enum class State{MONITOR,CAPTURE_BEFORE,DETERRENCE,WAIT_VERIFY,CAPTURE_AFTER,COMPLETE};
static State state=State::MONITOR;static uint32_t stateSince=0,lastAlarm=0;static uint8_t cycles=0;static AnimalClass detected=AnimalClass::UNKNOWN;static String beforePath,afterPath;
static void transition(State s){state=s;stateSince=millis();}
void setup(){Serial.begin(115200);delay(100);initializeSafety();initializeDeterrent();if(!initializeCamera()){Serial.println("CAMERA_ERROR");return;}if(!initializeImageStorage())Serial.println("SD_ERROR");initializeMotionDetection();initializeAnimalAI();initializeWiFi();initializeTelegram();transition(State::MONITOR);}
void loop(){serviceWiFi();serviceSafety();serviceTelegram();deterrentActive();serviceAudibleDeterrent();manageStorage();if(state==State::MONITOR&&millis()-lastAlarm>DETECTION_COOLDOWN_MS&&detectMotion())transition(State::CAPTURE_BEFORE);
if(state==State::CAPTURE_BEFORE){setPhotoMode();camera_fb_t*fb=capturePhoto();if(!fb){telegramText("Camera error during before capture");transition(State::MONITOR);return;}Classification r=classifyAnimal(fb->buf,fb->len);if(!verifyRepeatedDetection(r.label,r.confidence)){releasePhoto(fb);setMonitoringMode();transition(State::MONITOR);return;}detected=r.label;beforePath=savePhoto(fb->buf,fb->len,"before",r.label,r.confidence);releasePhoto(fb);setMonitoringMode();telegramText(String("Animal detected: ")+animalClassName(detected));cycles=0;transition(State::DETERRENCE);}
if(state==State::DETERRENCE){if(!safetyAllowsActuation()){telegramText("Deterrent inhibited by safety monitor");transition(State::MONITOR);}else{startDeterrent();telegramText("Deterrent activated");transition(State::WAIT_VERIFY);}}
if(state==State::WAIT_VERIFY&&millis()-stateSince>=VERIFY_WAIT_MS)transition(State::CAPTURE_AFTER);
if(state==State::CAPTURE_AFTER){setPhotoMode();camera_fb_t*fb=capturePhoto();if(!fb){telegramText("Camera error during after capture");transition(State::MONITOR);return;}Classification r=classifyAnimal(fb->buf,fb->len);afterPath=savePhoto(fb->buf,fb->len,"after",r.label,r.confidence);releasePhoto(fb);setMonitoringMode();if(r.label==detected&&r.confidence>=CLASSIFICATION_THRESHOLD){cycles++;if(cycles<MAX_DETERRENT_CYCLES)transition(State::DETERRENCE);else{telegramText("ANIMAL_STILL_PRESENT (visual result; physical removal not confirmed)");transition(State::COMPLETE);}}else{telegramText("ANIMAL_NO_LONGER_DETECTED (visual absence only; physical removal not confirmed)");transition(State::COMPLETE);}}if(state==State::COMPLETE&&millis()-stateSince>DETECTION_COOLDOWN_MS){lastAlarm=millis();transition(State::MONITOR);updateReferenceFrame();}delay(1);}

