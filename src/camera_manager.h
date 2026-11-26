#pragma once
#include <Arduino.h>
#include "esp_camera.h"
bool initializeCamera();
camera_fb_t *capturePhoto();
void releasePhoto(camera_fb_t *fb);
bool captureMotionFrame(uint8_t *gray, size_t length);
bool setMonitoringMode();
bool setPhotoMode();

