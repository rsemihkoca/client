#include <WiFiManagerLibrary.h>
#include <HTTPClientLibrary.h>
#include <HardwareLibrary.h>


HardwareLibrary hardwareLibrary;


HTTPClientLibrary httpClientLibrary;

WiFiManagerLibrary wifiManagerLibrary;



void setup() {
  wifiManagerLibrary.setupWiFi();
  String deviceId =  hardwareLibrary.getHardwareSerialNumber();

  BrokerResponse response = httpClientLibrary.postRequest("http://192.168.0.20:8000/client", deviceId, deviceId);

  Serial.println("Broker Credentials:");
  Serial.print("Broker: ");
  Serial.println(response.brokerCred.broker);
  Serial.print("Port: ");
  Serial.println(response.brokerCred.port);
  Serial.print("Client ID: ");
  Serial.println(response.brokerCred.client_id);
  Serial.print("Username: ");
  Serial.println(response.brokerCred.username);
  Serial.print("Password: ");
  Serial.println(response.brokerCred.password);

  for (const Topic& topic : response.topics) {
    Serial.print(topic.name);
    Serial.print(": ");
    Serial.println(topic.action);
  }

}

void loop() {
  wifiManagerLibrary.checkConnection();
  delay(5000); // Her 10 saniyede bir bağlantıyı kontrol et
}
