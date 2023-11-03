#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <handleLed.h>


// const int ledPin = D4; // Definiuj pin diody LED
// const int ledCPin = D3;
// const int ledWPin = D2;
//const char *ssid = "FunBox2-99AC";
//const char *password = "RBpc55EN";
const char *ssid = "Orange_Swiatlowod_6A50";
const char *password = "Q4Y2JKMJ2L6C";
ESP8266WebServer server(80);

void HTTP_handleLed(void);

void setup() {
  ledSetup();
  Serial.begin(9600);

  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Brak połączenia z WiFi...");
  }

  Serial.println("Połączono z WiFi"); 
  Serial.println(WiFi.localIP());
  server.on("/led_control", HTTP_POST, HTTP_handleLed);
  server.begin(); 
}

void loop() {
  server.handleClient();
}

void HTTP_handleLed(void){
  if (server.hasArg("command")) {
        String command = server.arg("command");
        if (command == "led_on") {
          handleLed(LedType::ledOn);
        } 
        else if (command == "led_off") {
          handleLed(LedType::ledOff);
        }
        else if (command == "cold_led_off")  {
          handleLed(LedType::ledCOff);
        }
        else if (command == "cold_led_on")
        {
          handleLed(LedType::ledCOn);
        }
        else if (command == "warm_led_off")  {
          handleLed(LedType::ledWOff);
        }
        else if (command == "warm_led_on")
        {
          handleLed(LedType::ledWOn);
        }
        else {
            server.send(400, "text/plain", "Nieznana komenda");
        }
    } else {
        server.send(400, "text/plain", "Brak komendy");
    }
}
