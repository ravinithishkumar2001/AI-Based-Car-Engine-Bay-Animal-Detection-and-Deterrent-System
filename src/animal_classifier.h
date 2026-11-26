#pragma once
#include <Arduino.h>
enum class AnimalClass:uint8_t{RAT,MOUSE,SQUIRREL,INSECT,BACKGROUND,UNKNOWN};
struct Classification{AnimalClass label;float confidence;float scores[5];bool valid;};
bool initializeAnimalAI();
Classification classifyAnimal(const uint8_t*,size_t);
float getAnimalConfidence(const Classification&);
bool verifyRepeatedDetection(AnimalClass,float);
const char* animalClassName(AnimalClass);

