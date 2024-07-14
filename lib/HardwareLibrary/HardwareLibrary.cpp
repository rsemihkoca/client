#include "HardwareLibrary.h"

HardwareLibrary::HardwareLibrary() {
  // Constructor
}

String HardwareLibrary::getHardwareSerialNumber() {
  uint64_t chipid = getChipId();
  String serialNumber = String((uint16_t)(chipid >> 32), HEX) + String((uint32_t)chipid, HEX);
  serialNumber.toUpperCase();
  return serialNumber;
}

uint64_t HardwareLibrary::getChipId() {
  return ESP.getEfuseMac();
}
