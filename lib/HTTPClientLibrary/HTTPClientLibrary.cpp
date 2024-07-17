#include "HTTPClientLibrary.h"
#include <ArduinoJson.h>

HTTPClientLibrary::HTTPClientLibrary() {
  // Constructor if needed
}

BrokerResponse HTTPClientLibrary::postRequest(const char* url, String clientId, String username) {
  BrokerResponse responseStruct;

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.setConnectTimeout(10000); // 10 second timeout
    http.setTimeout(10000); // 10 second timeout

    JsonDocument doc;
    doc["client_id"] = clientId;
    doc["username"] = username;
    String requestBody;
    serializeJson(doc, requestBody);

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
      responseStruct = parseResponse(response);
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Close the connection
  } else {
    Serial.println("WiFi Disconnected");
  }

  return responseStruct;
}

BrokerResponse HTTPClientLibrary::parseResponse(String response) {
  BrokerResponse responseStruct;

  JsonDocument doc; // Increased size to accommodate the response
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.print("Error parsing JSON: ");
    Serial.println(error.c_str());
    return responseStruct; // Return empty response on error
  }

  JsonObject broker_cred = doc["broker_cred"];
  responseStruct.brokerCred.broker = broker_cred["broker"].as<String>();
  responseStruct.brokerCred.port = broker_cred["port"];
  responseStruct.brokerCred.client_id = broker_cred["client_id"].as<String>();
  responseStruct.brokerCred.username = broker_cred["username"].as<String>();
  responseStruct.brokerCred.password = broker_cred["password"].as<String>();

/*   JsonArray topics = doc["topics"];
  for (JsonObject topicObj : topics) {
    for (JsonPair kv : topicObj) {
      Topic t;
      t.name = kv.key().c_str();
      t.action = kv.value().as<String>();
      responseStruct.topics.push_back(t);
    }
  } */

  return responseStruct;
}
