#include "camera_manager.h"
#include "config.h"
static bool configure(framesize_t size, pixformat_t format) { sensor_t *s=esp_camera_sensor_get(); if(!s)return false; s->set_pixformat(s,format); s->set_framesize(s,size); return true; }
bool initializeCamera(){ camera_config_t c{}; c.ledc_channel=LEDC_CHANNEL_0;c.ledc_timer=LEDC_TIMER_0;c.pin_d0=CAM_D0;c.pin_d1=CAM_D1;c.pin_d2=CAM_D2;c.pin_d3=CAM_D3;c.pin_d4=CAM_D4;c.pin_d5=CAM_D5;c.pin_d6=CAM_D6;c.pin_d7=CAM_D7;c.pin_xclk=CAM_XCLK;c.pin_pclk=CAM_PCLK;c.pin_vsync=CAM_VSYNC;c.pin_href=CAM_HREF;c.pin_sccb_sda=CAM_SIOD;c.pin_sccb_scl=CAM_SIOC;c.pin_pwdn=CAM_PWDN;c.pin_reset=CAM_RESET;c.xclk_freq_hz=20000000;c.pixel_format=PIXFORMAT_RGB565;c.frame_size=FRAMESIZE_QQVGA;c.jpeg_quality=12;c.fb_count=psramFound()?2:1;c.grab_mode=CAMERA_GRAB_LATEST;c.fb_location=CAMERA_FB_IN_PSRAM;return esp_camera_init(&c)==ESP_OK; }
bool setMonitoringMode(){return configure(FRAMESIZE_QQVGA,PIXFORMAT_RGB565);}
bool setPhotoMode(){return configure(FRAMESIZE_UXGA,PIXFORMAT_JPEG);}
bool captureMotionFrame(uint8_t *gray,size_t length){if(!gray||length<MOTION_WIDTH*MOTION_HEIGHT)return false;camera_fb_t*fb=esp_camera_fb_get();if(!fb||fb->format!=PIXFORMAT_RGB565){if(fb)esp_camera_fb_return(fb);return false;}const uint16_t*p=(const uint16_t*)fb->buf;for(size_t i=0;i<MOTION_WIDTH*MOTION_HEIGHT;i++){uint16_t v=p[i];uint8_t r=((v>>11)&31)<<3,g=((v>>5)&63)<<2,b=(v&31)<<3;gray[i]=(77*r+150*g+29*b)>>8;}esp_camera_fb_return(fb);return true;}
camera_fb_t* capturePhoto(){return esp_camera_fb_get();} void releasePhoto(camera_fb_t*fb){if(fb)esp_camera_fb_return(fb);}

