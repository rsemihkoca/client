#include "MQTTLibrary.h"

MQTTLibrary::MQTTLibrary() : _mqttClient(_wifiClient)
{
}

void MQTTLibrary::begin(const char *mqttServer, int mqttPort, const char *mqttClientId, const char *mqttUsername, const char *mqttPassword)
{
    this->_mqttClientId = mqttClientId;
    this->_mqttUsername = mqttUsername;
    this->_mqttPassword = mqttPassword;

    // Set MQTT server and port
    _mqttClient.setServer(mqttServer, mqttPort);

    // Set the global callback to handle incoming messages
    _mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->globalCallback(topic, payload, length);
    });

    // MQTT v5 specific settings
    _mqttClient.setKeepAlive(100);

    // Connect to the MQTT broker
    connectToMQTT();
}

void MQTTLibrary::loop()
{
    // Reconnect if the client is not connected
    if (!_mqttClient.connected())
    {
        reconnect();
    }
    _mqttClient.loop();
}

void MQTTLibrary::publish(const char *topic, const char *payload)
{
    _mqttClient.publish(topic, payload);
}

void MQTTLibrary::subscribe(const char *topic, MQTTCallback callback)
{
    // Store the callback in the map and subscribe to the topic
    _callbackMap[std::string(topic)] = callback;
    _mqttClient.subscribe(topic);
}

void MQTTLibrary::connectToMQTT()
{
    // Attempt to connect to the MQTT broker
    while (!_mqttClient.connected())
    {
        if (_mqttClient.connect(this->_mqttClientId, this->_mqttUsername, this->_mqttPassword))
        {
            // Resubscribe to all topics after reconnecting
            for (const auto &pair : _callbackMap)
            {
                _mqttClient.subscribe(pair.first.c_str());
            }
        }
        else
        {
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void MQTTLibrary::reconnect()
{
    connectToMQTT();
}

void MQTTLibrary::globalCallback(char *topic, byte *payload, unsigned int length)
{
    // Call the instance-specific callback handler
    handleCallback(topic, payload, length);
}

void MQTTLibrary::handleCallback(char *topic, byte *payload, unsigned int length)
{
    // Convert topic to a string
    std::string topicStr(topic);

    // Find the corresponding callback in the map and execute it
    if (_callbackMap.find(topicStr) != _callbackMap.end())
    {
        _callbackMap[topicStr](topic, payload, length);
    }
}
