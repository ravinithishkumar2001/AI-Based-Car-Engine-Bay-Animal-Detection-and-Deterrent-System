# Hardware checklist

- DFRobot DFR1154 V1.1: ESP32-S3R8, 16 MB flash, 8 MB PSRAM.
- FAT32 microSD (DFRobot documents maximum 32 GB).
- 4 Ω 1.5 W or 8 Ω 1 W speaker.
- External frequency-controlled ultrasonic generator/transducer with logic enable.
- Logic-level MOSFET interface, fuse, reverse-polarity protection, TVS and automotive 12 V-to-5 V converter.
- External temperature cutoff and optional protected voltage divider.

DFRobot's current product page has a camera inconsistency: its specification table says GC2145 while the board description and example ecosystem refer to OV3660. Inspect the physical module and validate with DFRobot's CameraWebServer before deployment; the pin map here is for the DFR1154 examples, not generic ESP32-CAM boards.

