#pragma once

#include <Arduino.h>

enum LedType {
    allLed,
    LedC,
    LedW,
    ledOn,
    ledOff,
    ledCOn,
    ledCOff,
    ledWOn,
    ledWOff
};

class LedHandler{
public:
    LedHandler(int pinLed, int pinLedC, int pinLedW);
    void ledSetup();
    void colorTemperatureLed(int value, int percentage);
    void handleLed(LedType type);
    void sliderLed(LedType type, int value);

private:
    int ledPin;
    int ledCPin;
    int ledWPin;
};