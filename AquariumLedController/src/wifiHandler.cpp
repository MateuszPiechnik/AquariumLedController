#include "wifiHandler.h"

const char *ssid = "Orange_Swiatlowod_6A50";
const char *password = "Q4Y2JKMJ2L6C";

void wifiSetup(){
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Brak połączenia z WiFi...");
  }

  Serial.println("Połączono z WiFi"); 
  Serial.println(WiFi.localIP());
}