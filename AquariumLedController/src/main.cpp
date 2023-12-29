#include <Arduino.h>
#include <wifiHandler.h>
#include <ESP8266WebServer.h>
#include <ledHandler.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

ESP8266WebServer server(80);

const int ledCPin = D3;
const int ledWPin = D2;

const char *ssid = "FunBox2-99AC";
const char *password = "RBpc55EN";

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
WifiHandler wifiHandler(ssid, password);

void setup() {
  ledHandler.ledSetup();
  Serial.begin(9600);
  wifiHandler.setup();

  timeClient.begin();
  timeClient.setTimeOffset(3600);
  
  server.on("/led_control", HTTP_POST, HTTP_handleLed);
  server.on("/sunrise_time", HTTP_GET, handleSunriseTime);
  server.on("/sunset_time", HTTP_GET, handleSunsetTime);
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
      Serial.println("Osiagnieto wprowadzona godzine, ustawiono wybrane parametry");
    }
    else if (actualTime == setTimeOff && turnOff == true)
    {
      ledHandler.handleLed(LedType::ledOff);
      turnOff = false;
      Serial.println("Osiagnieto wprowadzona godzine, wylaczono diody");
    }
    else if (turnOn == false && turnOff == false){
      isTimerOn = false;
    }
  }
  if (isDaySimOn)
  {
    timeClient.update();
    int actualTime = timeClient.getHours() * 100 + timeClient.getMinutes();
    ledHandler.daySimulation(actualTime, sunriseTime, sunsetTime);
  }

  server.handleClient();
}

void handleSunriseTime()
{
  if (server.args() > 0)
  {
    sunriseTime = server.arg("value").toInt();
    Serial.print("Wschód słońca: ");
    Serial.println(sunriseTime);
  }
}

void handleSunsetTime()
{
  if (server.args() > 0)
  {
    sunsetTime = server.arg("value").toInt();
    Serial.print("Zachod słońca: ");
    Serial.println(sunsetTime);
  }
}

void handleColorTemperature()
{
  if (server.args() > 0)
  {
    int colorTemperature = server.arg(0).toInt();
    int percentage = server.arg(1).toInt();
    Serial.print("Wybrana temperatura barwowa: ");
    Serial.println(colorTemperature);
    Serial.print("Wybrana intensywnosc światła : ");
    Serial.print(percentage);
    Serial.println("%");
    ledHandler.colorTemperatureLed(colorTemperature, percentage);
  }
}

void handleTimerOn()
{
  if (server.args() > 0)
  {
    setTimeOn = server.arg(0).toInt();
    timerCT = server.arg(1).toInt();
    timerBrightness = server.arg(2).toInt();
    turnOn = true;
    isTimerOn = true;
    Serial.print("Wlączono timer z ustawieniami na godzine: ");
    Serial.println(setTimeOn);
    Serial.print("Wybrana temperatura barwowa: ");
    Serial.println(timerCT);
    Serial.print("Wybrana intensywnosc swiatla: ");
    Serial.print(timerBrightness);
    Serial.println(" %");
  }
}

void handleTimerOff()
{
  if (server.args() > 0)
  {
    setTimeOff = server.arg("value").toInt();
    turnOff = true;
    isTimerOn = true;
    Serial.print("Obecne ustawienia zostaną wyłączone o:");
    Serial.println(setTimeOff);
  }
}

void handleSliderValue()
{
  if (server.args() > 0)
  {
    String value = server.arg("value");
    int intValue = value.toInt();
    ledHandler.sliderLed(LedType::allLed, intValue);
    Serial.print("Ustawiono intensywność obu diod na :");
    Serial.println((intValue/255 * 100));
  }
}

void handleSliderValueCold()
{
  if (server.args() > 0)
  {
    String value = server.arg("value");
    int intValue = value.toInt();
    ledHandler.sliderLed(LedType::LedC, intValue);
    Serial.print("Ustawiono intensywność diody zimnej na: ");
    Serial.print((intValue*100)/255);
    Serial.println("%");
  }
}

void handleSliderValueWarm()
{
  if (server.args() > 0)
  {
    String value = server.arg("value");
    int intValue = value.toInt();
    ledHandler.sliderLed(LedType::LedW, intValue);
    Serial.print("Ustawiono intensywnosc diody cieplej na: ");
    Serial.print((intValue*100)/255);
    Serial.println("%");
  }
}

void HTTP_handleLed(void)
{
  if (server.hasArg("command"))
  {
    String command = server.arg("command");
    if (command == "led_on")
    {
      Serial.println("Włączono wszystkie diody");
      ledHandler.handleLed(LedType::ledOn);
    }
    else if (command == "led_off")
    {
      Serial.println("Wyłączono wszystkie diody");
      ledHandler.handleLed(LedType::ledOff);
    }
    else if (command == "cold_led_off")
    {
      Serial.println("Wyłączono diody zimne");
      ledHandler.handleLed(LedType::ledCOff);
    }
    else if (command == "cold_led_on")
    {
      Serial.println("Włączono diody zimne");
      ledHandler.handleLed(LedType::ledCOn);
    }
    else if (command == "warm_led_off")
    {
      Serial.println("Wyłączono diody ciepłe");
      ledHandler.handleLed(LedType::ledWOff);
    }
    else if (command == "warm_led_on")
    {
      Serial.println("Włączono diody ciepłe");
      ledHandler.handleLed(LedType::ledWOn);
    }
    else if (command == "reset_time")
    {
      Serial.println("Zresetowano timer");
      isTimerOn = false;
    }
    else if (command == "day_sim_on")
    {
      Serial.println("Uruchomiono tryb symulacji dnia");
      isDaySimOn = true;
    }
    else if (command == "day_sim_off")
    {
      Serial.println("Wyłączono tryb symulacji dnia");
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
