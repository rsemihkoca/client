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

String deviceId = hardwareLibrary.getChipId();

bool exitFlag = false;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void callback1(char *topic, byte *payload, unsigned int length)
{
  // Handle messages for topic1
  Serial.print("Message received on command topic: ");
  Serial.write(payload, length);
  Serial.println();
}

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200

  // Initialize WiFi
  wifiManagerLibrary.setupWiFi();

  // Initialize time client
  timeClient.begin();
  // GMT+3
  timeClient.setTimeOffset(10800);

  // Initialize HTTP client and get broker response
  BrokerResponse response = httpClientLibrary.postRequest("http://192.168.0.28:8000/client", deviceId, deviceId);
  response.print();
  // Initialize MQTT client
  mqttClient.begin(response.brokerCred.broker.c_str(), response.brokerCred.port, response.brokerCred.client_id.c_str(), response.brokerCred.username.c_str(), response.brokerCred.password.c_str());

  String message = "Client " + deviceId + " at " + timeClient.getFormattedTime() + " is online";
  bool r1 = mqttClient.publish(hardwareLibrary.getCommandTopic(), message.c_str());
  bool r2 = mqttClient.publish(hardwareLibrary.getInferenceTopic(), message.c_str());
  bool r3 = mqttClient.publish(hardwareLibrary.getLogTopic(), message.c_str());
  bool r4 = mqttClient.publish(hardwareLibrary.getStateTopic(), message.c_str());
  bool r5 = mqttClient.subscribe(hardwareLibrary.getCommandTopic(), callback1);

  if (r1 && r2 && r3 && r4 && r5)
  {
    Serial.println("Successfully published and subscribed to topics");
  }
  else
  {
    exitFlag = true;
    Serial.println("Failed to publish or subscribe to topics");
  }
}

void loop()
{

  if (exitFlag)
  {
    Serial.println("Exiting...");
    delay(1000);
    ESP.restart();
  }

  wifiManagerLibrary.checkConnection();

  mqttClient.loop();
  timeClient.update();

  delay(5000);
  Serial.println(timeClient.getFormattedTime());

  String message = "Client " + deviceId + " at " + timeClient.getFormattedTime() + " is online";
  Serial.println(message);
  mqttClient.publish(hardwareLibrary.getCommandTopic(), message.c_str());
  mqttClient.publish(hardwareLibrary.getInferenceTopic(), message.c_str());
  mqttClient.publish(hardwareLibrary.getLogTopic(), message.c_str());
  mqttClient.publish(hardwareLibrary.getStateTopic(), message.c_str());
}
