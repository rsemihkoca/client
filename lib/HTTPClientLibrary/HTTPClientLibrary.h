#ifndef HTTPClientLibrary_h
#define HTTPClientLibrary_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>

struct BrokerCredentials
{
  String broker;
  int port;
  String client_id;
  String username;
  String password;
};

struct Topic
{
  String name;
  String action;
};

struct BrokerResponse
{
  BrokerCredentials brokerCred;
  // std::vector<Topic> topics;

  void print()
  {

    if (brokerCred.broker.length() > 0)
    {

      Serial.println("#######################");
      Serial.println("Broker Credentials:");
      Serial.print("Broker: ");
      Serial.println(brokerCred.broker);
      Serial.print("Port: ");
      Serial.println(brokerCred.port);
      Serial.print("Client ID: ");
      Serial.println(brokerCred.client_id);
      Serial.print("Username: ");
      Serial.println(brokerCred.username);
      Serial.print("Password: ");
      Serial.println(brokerCred.password);

      // Serial.println("Topics:");
      // for (const Topic &topic : topics)
      // {
        // Serial.print(topic.name);
        // Serial.print(": ");
        // Serial.println(topic.action);
      // }
      Serial.println("#######################");
    }
    else
    {
      Serial.println("Failed to retrieve broker credentials");
    }
  }
};

class HTTPClientLibrary
{
public:
  HTTPClientLibrary();
  BrokerResponse postRequest(const char *url, String clientId, String username);

private:
  BrokerResponse parseResponse(String response);
};

#endif
