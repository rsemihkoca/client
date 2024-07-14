#ifndef HardwareLibrary_h
#define HardwareLibrary_h

#include <Arduino.h>

class HardwareLibrary {
  public:
    HardwareLibrary();
    String getHardwareSerialNumber();
  
  private:
    uint64_t getChipId();
};

#endif
