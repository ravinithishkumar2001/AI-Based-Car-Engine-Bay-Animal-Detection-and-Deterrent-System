# AI car engine-bay animal detector and deterrent

PlatformIO prototype for the DFRobot DFR1154 ESP32-S3 AI Camera V1.1. It provides camera motion detection, SD photo logging, Wi-Fi/NTP, a safe Edge Impulse integration seam, and independently timed GPIO43 ultrasonic-generator enable. GPIO44 is deliberately unused.

The classifier is intentionally a non-operational placeholder until a trained INT8 Edge Impulse Arduino/TFLite Micro library is installed. It returns `UNKNOWN`, so the deterrent cannot trigger. See [ai_model_training.md](ai_model_training.md).

Copy `include/secrets.h.example` to `include/secrets.h`, fill credentials, then run `pio run`. Use a FAT32 microSD card up to 32 GB. The board's external VIN still needs an automotive-rated fused, protected 12 V-to-5 V supply.

Hardware references: [DFRobot DFR1154 documentation](https://wiki.dfrobot.com/dfr1154/), [V1.1 schematic](https://dfimg.dfrobot.com/62d52567aa9508d63a4247a1/wikien/62f7850198e513d61ce2e02ecde3eb42.pdf), and [DFRobot examples](https://github.com/DFRobot/DFR1154_Examples).

