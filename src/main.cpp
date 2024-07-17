#include <HardwareLibrary.h>
#include <HTTPClientLibrary.h>
#include <WiFiManagerLibrary.h>
#include <MQTTLibrary.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


HardwareLibrary hardwareLibrary;

HTTPClientLibrary httpClientLibrary;

WiFiManagerLibrary wifiManagerLibrary;

MQTTLibrary mqttClient;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void callback1(char* topic, byte* payload, unsigned int length) {
    // Handle messages for topic1
    Serial.print("Message received on command topic: ");
    Serial.write(payload, length);
    Serial.println();
}

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200
  // timeClient.begin();
  //GMT+3
  // timeClient.setTimeOffset(10800);
  wifiManagerLibrary.setupWiFi();
  String deviceId = hardwareLibrary.getChipId();

  BrokerResponse response = httpClientLibrary.postRequest("http://192.168.0.20:8000/client", deviceId, deviceId);
  response.print();

/*   mqttClient.begin(response.brokerCred.broker.c_str(), response.brokerCred.port, response.brokerCred.client_id.c_str(), response.brokerCred.username.c_str(), response.brokerCred.password.c_str());
  
  String message = "Client " + deviceId + " at " + timeClient.getFormattedTime() + " is online";
  mqttClient.publish(hardwareLibrary.getCommandTopic(), message.c_str());
  mqttClient.publish(hardwareLibrary.getInferenceTopic(), message.c_str());
  mqttClient.publish(hardwareLibrary.getLogTopic(), message.c_str());
  mqttClient.publish(hardwareLibrary.getStateTopic(), message.c_str());
  mqttClient.subscribe(hardwareLibrary.getCommandTopic(), callback1); */

}

void loop() {
  wifiManagerLibrary.checkConnection();
  // mqttClient.loop();
  // timeClient.update();

  delay(1000);
  // String message = "Client " + deviceId + " at " + timeClient.getFormattedTime() + " is online";
  // mqttClient.publish(hardwareLibrary.getCommandTopic(), message.c_str());
  // mqttClient.publish(hardwareLibrary.getInferenceTopic(), message.c_str());
  // mqttClient.publish(hardwareLibrary.getLogTopic(), message.c_str());
  // mqttClient.publish(hardwareLibrary.getStateTopic(), message.c_str());

}


