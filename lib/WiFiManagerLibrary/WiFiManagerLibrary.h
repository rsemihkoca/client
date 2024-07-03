#ifndef WiFiManagerLibrary_h
#define WiFiManagerLibrary_h

#include <WiFi.h>
#include <WiFiManager.h>

class WiFiManagerLibrary {
  public:
    WiFiManagerLibrary();
    void setupWiFi();
    void checkConnection();
  
  private:
    WiFiManager wifiManager;
    String generateSSID();
    const char* password = "123456fd";
};

#endif
