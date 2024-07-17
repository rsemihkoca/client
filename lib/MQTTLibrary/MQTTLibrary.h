#ifndef MQTTLIBRARY_H
#define MQTTLIBRARY_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <map>
#include <string>

// Type alias for MQTT callback function
typedef std::function<void(char*, byte*, unsigned int)> MQTTCallback;

class MQTTLibrary
{
public:
    // Constructor
    MQTTLibrary();

    // Initialize the MQTT client with server details and credentials
    void begin(const char *mqttServer, int mqttPort, const char *mqttClientId, const char *mqttUsername, const char *mqttPassword);

    // Main loop to keep the MQTT client running
    void loop();

    // Publish a message to a specific topic
    void publish(const char *topic, const char *payload);

    // Subscribe to a specific topic with a callback function
    void subscribe(const char *topic, MQTTCallback callback);

private:
    // Reconnect to the MQTT broker
    void reconnect();

    // Establish connection to the MQTT broker
    void connectToMQTT();

    // Handle incoming messages and dispatch them to the correct callback
    void handleCallback(char *topic, byte *payload, unsigned int length);

    // Global callback function to handle messages
    void globalCallback(char *topic, byte *payload, unsigned int length);

    // WiFi client object
    WiFiClient _wifiClient;

    // MQTT client object
    PubSubClient _mqttClient;

    // MQTT connection details
    const char *_mqttClientId;
    const char *_mqttUsername;
    const char *_mqttPassword;

    // Map to store callbacks for each subscribed topic
    std::map<std::string, MQTTCallback> _callbackMap;
};

#endif // MQTTLIBRARY_H
