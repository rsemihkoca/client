#include <WiFiManagerLibrary.h>
#include <HTTPClientLibrary.h>
#include <HardwareLibrary.h>


HardwareLibrary hardwareLibrary;


HTTPClientLibrary httpClientLibrary;

WiFiManagerLibrary wifiManagerLibrary;



void setup() {
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200

  wifiManagerLibrary.setupWiFi();
  String deviceId =  hardwareLibrary.getHardwareSerialNumber();

  BrokerResponse response = httpClientLibrary.postRequest("http://192.168.0.20:8000/client", deviceId, deviceId);

  // Check if the response contains valid data
  if (response.brokerCred.broker.length() > 0) {
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

    Serial.println("Topics:");
    for (const Topic& topic : response.topics) {
      Serial.print(topic.name);
      Serial.print(": ");
      Serial.println(topic.action);
    }
  } else {
    Serial.println("Failed to retrieve broker credentials");
  }
}

void loop() {
  wifiManagerLibrary.checkConnection();
  delay(5000); // Her 10 saniyede bir bağlantıyı kontrol et
}
