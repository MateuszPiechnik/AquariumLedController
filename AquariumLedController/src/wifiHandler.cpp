#include "wifiHandler.h"


WifiHandler::WifiHandler(const char* ssid, const char* password) : ssid(ssid), password(password) {}

void WifiHandler::setup(){
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Brak połączenia z WiFi...");
  }

  Serial.println("Połączono z WiFi");
  Serial.println(WiFi.localIP());
}