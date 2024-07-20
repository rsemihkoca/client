#include "MQTTLibrary.h"

MQTTLibrary::MQTTLibrary() : _mqttClient(_wifiClient)
{
}

void MQTTLibrary::begin(const char *mqttServer, int mqttPort, const char *mqttClientId, const char *mqttUsername, const char *mqttPassword)
{
    this->_mqttClientId = mqttClientId;
    this->_mqttUsername = mqttUsername;
    this->_mqttPassword = mqttPassword;

    IPAddress mqtt_server_ip;
    mqtt_server_ip.fromString(mqttServer);
    // Set MQTT server and port
    _mqttClient.setServer(mqtt_server_ip, mqttPort);

    // Set the global callback to handle incoming messages
    _mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->globalCallback(topic, payload, length);
    });

    // MQTT v5 specific settings
    _mqttClient.setKeepAlive(100);

    // Connect to the MQTT broker
    connectToMQTT();
    Serial.println("MQTT client initialized");
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

bool MQTTLibrary::publish(const char *topic, const char *payload)
{
    bool result = _mqttClient.publish(topic, (const uint8_t *)payload, strlen(payload));
    if (!result)
    {
        Serial.println("Failed to publish message");
        Serial.print("MQTT state: ");
        Serial.println(_mqttClient.state());
    }

    return result;
}

bool MQTTLibrary::subscribe(const char *topic, MQTTCallback callback)
{
    // Store the callback in the map and subscribe to the topic
    _callbackMap[std::string(topic)] = callback;
    bool result = _mqttClient.subscribe(topic);
    if (!result)
    {
        Serial.println("Failed to subscribe to topic");
        Serial.print("MQTT state: ");
        Serial.println(_mqttClient.state());
    }

    return result;
}

void MQTTLibrary::connectToMQTT()
{
    // Attempt to connect to the MQTT broker
    while (!_mqttClient.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (_mqttClient.connect(this->_mqttClientId, this->_mqttUsername, this->_mqttPassword), true)
        {
            Serial.println("Connected");
            for (const auto &pair : _callbackMap)
            {
                Serial.print("Subscribing to topic: ");
                Serial.println(pair.first.c_str());
                _mqttClient.subscribe(pair.first.c_str());
            }
        }
        Serial.print("Failed to connect to MQTT broker, rc=");
        Serial.print(_mqttClient.state());
        
        delay(5000);
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
