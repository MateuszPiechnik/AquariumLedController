#include <Arduino.h>
#include <wifiHandler.h>
#include <ESP8266WebServer.h>
#include <ledHandler.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

ESP8266WebServer server(80);

const int ledCPin = D3;
const int ledWPin = D2;

bool isTimerOn = false;
bool turnOn = false;
bool turnOff = false;
bool isDaySimOn = false;
int setTimeOn = 0;
int setTimeOff =0;
int timerCT = 0;
int timerBrightness=0;
int sunsetTime = 0;
int sunriseTime=0;
int previousTime;

void HTTP_handleLed(void);
void handleSliderValue(void);
void handleSliderValueCold(void);
void handleSliderValueWarm(void);
void handleTimerOn(void);
void handleTimerOff(void);
void handleColorTemperature(void);
void handleSunriseTime(void);
void handleSunsetTime(void);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
LedHandler ledHandler(D4, ledCPin, ledWPin);

void setup() {
  ledHandler.ledSetup();
  Serial.begin(9600);
  wifiSetup();

  timeClient.begin();
  timeClient.setTimeOffset(3600);

  server.on("/sunrise_time", HTTP_GET, handleSunriseTime);
  server.on("/sunset_time", HTTP_GET, handleSunsetTime);
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
    if (actualTime == setTimeOn && turnOn == true)
    {
      ledHandler.colorTemperatureLed(timerCT, timerBrightness);
      turnOn = false;
    }
    else if (actualTime == setTimeOff && turnOff == true)
    {
      ledHandler.handleLed(LedType::ledOff);
      turnOff = false;
    }
    else if (turnOn == false && turnOff == false){
      isTimerOn = false;
    }
  }

  if (isDaySimOn)
  {
    timeClient.update();
    int actualTime = timeClient.getHours() * 100 + timeClient.getMinutes();
    if (actualTime - previousTime != 0) //aktualizuj dane co minute
    {
      if (actualTime < sunriseTime || actualTime > sunsetTime)
      {
        digitalWrite(ledWPin, LOW);
        digitalWrite(ledCPin, LOW);
      }
      else if (actualTime == sunriseTime || actualTime == sunsetTime)
      {
        digitalWrite(ledWPin, HIGH);
        digitalWrite(ledCPin, LOW);
      }
      else if (actualTime == 1200)
      {
        digitalWrite(ledWPin, LOW);
        digitalWrite(ledCPin, HIGH);
      }
      else if (actualTime > sunriseTime && actualTime < 900)
      {
        int brightness = map(actualTime, sunriseTime, 900, 0, 255);
        digitalWrite(ledWPin, HIGH);
        analogWrite(ledCPin, brightness);
      }
      else if (actualTime > 900 && actualTime < 1200)
      {
        int brightness = map(actualTime, 900, 1200, 255, 0);
        digitalWrite(ledCPin, HIGH);
        analogWrite(ledWPin, brightness);
      }
      else if (actualTime > 1200 && actualTime < 1500)
      {
        int brightness = map(actualTime, 1200, 1500, 0, 255);
        digitalWrite(ledCPin, HIGH);
        analogWrite(ledWPin, brightness);
      }
      else if (actualTime > 1500 && actualTime < sunsetTime)
      {
        int brightness = map (actualTime,1500, sunsetTime, 255,0);
        digitalWrite(ledWPin, HIGH);
        analogWrite(ledCPin, brightness);
      }
      else if (actualTime == 900 || actualTime == 1500)
      {
        digitalWrite(ledWPin, HIGH);
        digitalWrite(ledCPin, HIGH);
      }
      Serial.println(actualTime);
      previousTime = actualTime;
    }
  }

  server.handleClient();
}

void handleSunriseTime(){
  if (server.args() > 0){
    sunriseTime = server.arg("value").toInt();
    Serial.println(sunriseTime);
  }
}

void handleSunsetTime(){
  if (server.args() > 0){
    sunsetTime = server.arg("value").toInt();
    Serial.println(sunsetTime);
  }
}


void handleColorTemperature(){
  if (server.args() > 0)
  {
    int colorTemperature = server.arg(0).toInt();
    int percentage = server.arg(1).toInt();
    ledHandler.colorTemperatureLed(colorTemperature, percentage);
  }
}

void handleTimerOn(){
  if(server.args()>0){
    setTimeOn = server.arg(0).toInt();
    timerCT = server.arg(1).toInt();
    timerBrightness = server.arg(2).toInt();
    turnOn = true;
    isTimerOn = true;
  }
}

void handleTimerOff(){
  if (server.args() > 0)
  {
    setTimeOff = server.arg("value").toInt();
    turnOff = true;
    isTimerOn = true;
  }
}

void handleSliderValue(){
  if(server.args()>0){
    String value = server.arg("value");
    int intValue = value.toInt();
    ledHandler.sliderLed(LedType::allLed, intValue);
  }
}

void handleSliderValueCold(){
  if(server.args()>0){
    String value = server.arg("value");
    int intValue = value.toInt();
    ledHandler.sliderLed(LedType::LedC, intValue);
  }
}

  void handleSliderValueWarm(){
  if(server.args()>0){
    String value = server.arg("value");
    int intValue = value.toInt();
    ledHandler.sliderLed(LedType::LedW, intValue);
  }
}

void HTTP_handleLed(void)
{
  if (server.hasArg("command"))
  {
    String command = server.arg("command");
    if (command == "led_on")
    {
      ledHandler.handleLed(LedType::ledOn);
    }
    else if (command == "led_off")
    {
      ledHandler.handleLed(LedType::ledOff);
    }
    else if (command == "cold_led_off")
    {
      ledHandler.handleLed(LedType::ledCOff);
    }
    else if (command == "cold_led_on")
    {
      ledHandler.handleLed(LedType::ledCOn);
    }
    else if (command == "warm_led_off")
    {
      ledHandler.handleLed(LedType::ledWOff);
    }
    else if (command == "warm_led_on")
    {
      ledHandler.handleLed(LedType::ledWOn);
    }
    else if (command == "reset_time"){
      isTimerOn = false;
    }
    else if (command == "day_sim_on"){
      isDaySimOn = true;
      previousTime = 0;
    }
    else if (command == "day_sim_off"){
      isDaySimOn = false;
    }
    else
    {
      server.send(400, "text/plain", "Unknown command");
    }
  }
  else
  {
    server.send(400, "text/plain", "No command");
  }
}
