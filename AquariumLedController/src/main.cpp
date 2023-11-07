#include <Arduino.h>
#include <wifiHandler.h>
#include <ESP8266WebServer.h>
#include <ledHandler.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

ESP8266WebServer server(80);

bool isTimerOn = false;
bool turnOn = false;
int setTime = 0;

void HTTP_handleLed(void);
void handleSliderValue(void);
void handleSliderValueCold(void);
void handleSliderValueWarm(void);
void handleTimerOn(void);
void handleTimerOff(void);
void handleColorTemperature(void);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  ledSetup();
  Serial.begin(9600);
  wifiSetup();

  timeClient.begin();
  timeClient.setTimeOffset(3600);

  server.on("/led_control", HTTP_POST, HTTP_handleLed);
  server.on("/set_value", HTTP_GET, handleSliderValue);
  server.on("/color_temperature", HTTP_GET, handleColorTemperature);
  server.on("/set_value_cold", HTTP_GET, handleSliderValueCold);
  server.on("/set_value_warm", HTTP_GET, handleSliderValueWarm);
  server.on("/time_on", HTTP_GET, handleTimerOn);
  server.on("/time_off", HTTP_GET, handleTimerOff);

  server.begin(); 
}

void loop() {

  if(isTimerOn){
    timeClient.update();
    int actualTime = timeClient.getHours() * 100 + timeClient.getMinutes();
    if (actualTime == setTime && turnOn == true)
    {
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledCPin, HIGH);
      digitalWrite(ledWPin, HIGH);
      isTimerOn = false;
      turnOn = false;
    }
    else if (actualTime == setTime && turnOn == false)
    {
      digitalWrite(ledPin, LOW);
      digitalWrite(ledWPin, LOW);
      digitalWrite(ledCPin, LOW);
      isTimerOn = false;
    }
  }
  server.handleClient();
}

void handleColorTemperature(){
  if (server.args() > 0)
  {
    int colorTemperature = server.arg("value").toInt();
    colorTemperatureLed(colorTemperature);
    Serial.println(colorTemperature);
  }
}

void handleTimerOn(){
  if(server.args()>0){
    setTime = server.arg("value").toInt();
    Serial.println(setTime);
    turnOn = true;
    isTimerOn = true;
  }
}

void handleTimerOff(){
  if (server.args() > 0)
  {
    setTime = server.arg("value").toInt();
    Serial.println(setTime);
    turnOn = false;
    isTimerOn = true;
  }
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
    else if (command == "reset_time"){
      isTimerOn = false;
      Serial.println("reset");
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
