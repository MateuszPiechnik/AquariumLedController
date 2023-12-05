#pragma once

#include <ESP8266WiFi.h>

class WifiHandler{

public:
    WifiHandler(const char* ssid, const char* password);
    void setup();

private:
    const char* ssid;
    const char* password;
};
