#ifndef HardwareLibrary_h
#define HardwareLibrary_h

#include <Arduino.h>

class HardwareLibrary {
public:
    HardwareLibrary();
    char* getChipId();
    char* getLogTopic();
    char* getInferenceTopic();
    char* getCommandTopic();
    char* getStateTopic();

private:
    char* getHardwareSerialNumber();
    char deviceId[17];  // Assuming a maximum of 16 characters for the device ID + null terminator
    char logTopic[50];  // Adjust the size as per your topic needs
    char inferenceTopic[50];  // Adjust the size as per your topic needs
    char commandTopic[50];  // Adjust the size as per your topic needs
    char stateTopic[50];  // Adjust the size as per your topic needs
};

#endif
