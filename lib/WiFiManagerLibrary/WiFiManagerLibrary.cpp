#include "WiFiManagerLibrary.h"

WiFiManagerLibrary::WiFiManagerLibrary() {
  // Constructor
}

void WiFiManagerLibrary::setupWiFi() {
  delay(1000);

  String ssid = generateSSID();

  // WiFi bağlantısı için portalı başlat
  wifiManager.autoConnect(ssid.c_str(), password);

  // Bağlantı sağlandığında WiFi bilgilerini yazdır
  Serial.println("Connected to WiFi!");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void WiFiManagerLibrary::checkConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, waiting for WiFi credentials...");
    
    String ssid = generateSSID();
    // wifiManager.setCustomHeadElement("<style>body{background-color: #f0f0f0; font-family: Arial, sans-serif;}</style>");
    // wifiManager.setCustomHeadElement("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    wifiManager.startConfigPortal(ssid.c_str(), password);
  }
}

String WiFiManagerLibrary::generateSSID() {
  uint32_t chipId = 0;
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return "ESP32_" + String(chipId);
}
