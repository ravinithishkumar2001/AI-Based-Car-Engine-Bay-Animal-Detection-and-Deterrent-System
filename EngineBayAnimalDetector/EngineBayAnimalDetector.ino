// Arduino IDE compatibility wrapper.
// PlatformIO builds src/*.cpp normally; Arduino IDE compiles these source files
// into one sketch translation unit.
#include "../src/camera_manager.cpp"
#include "../src/motion_detector.cpp"
#include "../src/animal_classifier.cpp"
#include "../src/image_storage.cpp"
#include "../src/wifi_manager.cpp"
#include "../src/telegram_manager.cpp"
#include "../src/deterrent_controller.cpp"
#include "../src/safety_manager.cpp"
#include "../src/main.cpp"
