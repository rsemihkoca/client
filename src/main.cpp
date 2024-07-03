#include <WiFiManagerLibrary.h>

WiFiManagerLibrary wifiManagerLibrary;

void setup() {
  wifiManagerLibrary.setupWiFi();
}

void loop() {
  wifiManagerLibrary.checkConnection();
  delay(10000); // Her 10 saniyede bir bağlantıyı kontrol et
}
