# Troubleshooting

- Camera init fails: reseat the flex cable, confirm V1.1, and run DFRobot's CameraWebServer first.
- DMA/heap errors: enable OPI PSRAM, reduce frame buffers and keep the Arduino core stable.
- SD fails: use FAT32 <=32 GB and verify the V1.1 1-bit SD pins.
- Telegram fails: confirm 2.4 GHz Wi-Fi, DNS/NTP and bot permissions; replace bench TLS handling with a pinned CA certificate for production.
- False alarms: increase thresholds/cooldown, improve mounting, expand `background`, and require more repeated model detections.
- “No longer detected” means absent from the camera view only, not proof of physical removal.

