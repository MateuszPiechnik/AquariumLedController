#include <Arduino.h>
#include <wifiHandler.h>
#include <ESP8266WebServer.h>
#include <ledHandler.h>

ESP8266WebServer server(80);

void HTTP_handleLed(void);
void handleSliderValue();
void handleSliderValueCold();
void handleSliderValueWarm();

void setup() {
  ledSetup();
  Serial.begin(9600);
  wifiSetup();

  server.on("/led_control", HTTP_POST, HTTP_handleLed);
  server.on("/set_value", HTTP_GET, handleSliderValue);
  server.on("/set_value_cold", HTTP_GET, handleSliderValueCold);
  server.on("/set_value_warm", HTTP_GET, handleSliderValueWarm);

  server.begin(); 
}

void loop() {
  server.handleClient();
}

void handleSliderValue(){
  if(server.args()>0){
    String value = server.arg("value");
    int intValue = value.toInt();
    Serial.println(value);
    sliderLed(LedType::allLed, intValue);
  }
}

void handleSliderValueCold(){
  if(server.args()>0){
    String value = server.arg("value");
    int intValue = value.toInt();
    Serial.println(value);
    sliderLed(LedType::LedC, intValue);
  }
}

  void handleSliderValueWarm(){
  if(server.args()>0){
    String value = server.arg("value");
    int intValue = value.toInt();
    Serial.println(value);
    sliderLed(LedType::LedW, intValue);
  }
}

void HTTP_handleLed(void)
{
  if (server.hasArg("command"))
  {
    String command = server.arg("command");
    if (command == "led_on")
    {
      handleLed(LedType::ledOn);
    }
    else if (command == "led_off")
    {
      handleLed(LedType::ledOff);
    }
    else if (command == "cold_led_off")
    {
      handleLed(LedType::ledCOff);
    }
    else if (command == "cold_led_on")
    {
      handleLed(LedType::ledCOn);
    }
    else if (command == "warm_led_off")
    {
      handleLed(LedType::ledWOff);
    }
    else if (command == "warm_led_on")
    {
      handleLed(LedType::ledWOn);
    }
    else
    {
      server.send(400, "text/plain", "Nieznana komenda");
    }
  }
  else
  {
    server.send(400, "text/plain", "Brak komendy");
  }
}
