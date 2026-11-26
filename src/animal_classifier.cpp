#include "animal_classifier.h"
#include "config.h"
static AnimalClass previous=AnimalClass::UNKNOWN;static uint8_t repeats=0;
bool initializeAnimalAI(){return true;}
Classification classifyAnimal(const uint8_t*,size_t){Classification r{};r.label=AnimalClass::UNKNOWN;r.valid=false;r.confidence=0;return r;}
bool verifyRepeatedDetection(AnimalClass l,float c){if(l==AnimalClass::UNKNOWN||l==AnimalClass::BACKGROUND||c<CLASSIFICATION_THRESHOLD){repeats=0;previous=l;return false;}repeats=l==previous?repeats+1:1;previous=l;return repeats>=REQUIRED_REPEATED_DETECTIONS;}
float getAnimalConfidence(const Classification&r){return r.confidence;}
const char* animalClassName(AnimalClass l){switch(l){case AnimalClass::RAT:return "rat";case AnimalClass::MOUSE:return "mouse";case AnimalClass::SQUIRREL:return "squirrel";case AnimalClass::INSECT:return "insect";case AnimalClass::BACKGROUND:return "background";default:return "unknown";}}

