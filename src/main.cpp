#include <WiFi.h>
#include <WiFiManager.h> 

WiFiManager wifiManager;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Cihazın seri numarasını (chip ID) al
  uint32_t chipId = 0;
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  String ssid = "ESP32_" + String(chipId);
  const char *password = "123456fd";

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

void loop() {
  // WiFi bağlantısını sürekli olarak kontrol et
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, waiting for WiFi credentials...");
    
    // SSID ve şifreyi tekrar tanımla
    uint32_t chipId = 0;
    for(int i=0; i<17; i=i+8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    String ssid = "ESP32_" + String(chipId);
    const char *password = "123456fd";

    wifiManager.startConfigPortal(ssid.c_str(), password);
  }
  delay(10000); // Her 10 saniyede bir bağlantıyı kontrol et
}
