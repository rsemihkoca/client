#include "HardwareLibrary.h"

HardwareLibrary::HardwareLibrary()
{
  // Get the hardware serial number and assign it to the class member
  strncpy(deviceId, getHardwareSerialNumber(), sizeof(deviceId) - 1);
  deviceId[sizeof(deviceId) - 1] = '\0'; // Ensure null termination

  // Initialize topic arrays
  snprintf(logTopic, sizeof(logTopic), "CLIENT/%s/LOG", deviceId);
  snprintf(inferenceTopic, sizeof(inferenceTopic), "CLIENT/%s/INFERENCE", deviceId);
  snprintf(commandTopic, sizeof(commandTopic), "CLIENT/%s/COMMAND", deviceId);
  snprintf(stateTopic, sizeof(stateTopic), "CLIENT/%s/STATE", deviceId);
}

char *HardwareLibrary::getHardwareSerialNumber()
{
  uint64_t chipid = ESP.getEfuseMac();
  static char serialNumber[17];
  snprintf(serialNumber, sizeof(serialNumber), "%04X%08X", (uint16_t)(chipid >> 32), (uint32_t)chipid);
  for (size_t i = 0; i < sizeof(serialNumber); ++i)
  {
    serialNumber[i] = toupper(serialNumber[i]);
  }

  return serialNumber;
}
char *HardwareLibrary::getChipId()
{
  return deviceId;
}

char *HardwareLibrary::getLogTopic()
{
  return logTopic;
}

char *HardwareLibrary::getInferenceTopic()
{
  return inferenceTopic;
}

char *HardwareLibrary::getCommandTopic()
{
  return commandTopic;
}

char *HardwareLibrary::getStateTopic()
{
  return stateTopic;
}
