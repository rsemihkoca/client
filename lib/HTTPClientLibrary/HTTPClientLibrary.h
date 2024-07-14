#ifndef HTTPClientLibrary_h
#define HTTPClientLibrary_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>

struct BrokerCredentials {
  String broker;
  int port;
  String client_id;
  String username;
  String password;
};

struct Topic {
  String name;
  String action;
};

struct BrokerResponse {
  BrokerCredentials brokerCred;
  std::vector<Topic> topics;
};

class HTTPClientLibrary {
  public:
    HTTPClientLibrary();
    BrokerResponse postRequest(const char* url, String clientId, String username);
  
  private:
    BrokerResponse parseResponse(String response);
};

#endif
