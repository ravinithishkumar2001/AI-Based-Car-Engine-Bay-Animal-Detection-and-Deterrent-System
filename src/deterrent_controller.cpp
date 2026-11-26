#include "deterrent_controller.h"
#include "config.h"
#include "driver/i2s.h"
#include <math.h>
static bool active=false;static uint32_t until=0;
static bool audioReady=false;static uint32_t audioUntil=0;static uint32_t phase=0;
void initializeDeterrent(){pinMode(ULTRASONIC_ENABLE_GPIO,OUTPUT);digitalWrite(ULTRASONIC_ENABLE_GPIO,LOW);i2s_config_t cfg{};cfg.mode=(i2s_mode_t)(I2S_MODE_MASTER|I2S_MODE_TX);cfg.sample_rate=16000;cfg.bits_per_sample=I2S_BITS_PER_SAMPLE_16BIT;cfg.channel_format=I2S_CHANNEL_FMT_ONLY_LEFT;cfg.communication_format=I2S_COMM_FORMAT_STAND_I2S;cfg.intr_alloc_flags=0;cfg.dma_buf_count=4;cfg.dma_buf_len=128;cfg.use_apll=false;cfg.tx_desc_auto_clear=true;cfg.fixed_mclk=0;if(i2s_driver_install(I2S_NUM_0,&cfg,0,nullptr)==ESP_OK){i2s_pin_config_t pins{(gpio_num_t)AUDIO_BCLK,(gpio_num_t)AUDIO_LRC,(gpio_num_t)AUDIO_DOUT,GPIO_NUM_NC};audioReady=i2s_set_pin(I2S_NUM_0,&pins)==ESP_OK;}}
void startDeterrent(){digitalWrite(ULTRASONIC_ENABLE_GPIO,HIGH);active=true;until=millis()+DETERRING_MS;audioUntil=millis()+1200;}
void stopDeterrent(){digitalWrite(ULTRASONIC_ENABLE_GPIO,LOW);active=false;}
bool deterrentActive(){if(active&&(int32_t)(millis()-until)>=0)stopDeterrent();return active;}
void serviceAudibleDeterrent(){if(!audioReady||millis()>audioUntil)return;int16_t buf[128];for(int i=0;i<128;i++){buf[i]=(int16_t)(sin((phase++%80)*2.0f*PI/80.0f)*7000);}size_t written=0;i2s_write(I2S_NUM_0,buf,sizeof(buf),&written,0);}

