#pragma once

#include <Arduino.h>
#include <string>

const int ledPin = D4;
const int ledCPin = D3;
const int ledWPin = D2;

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

void colorTemperatureLed(int value);
void handleLed(LedType type);
void sliderLed(LedType type, int value);
void ledSetup(void);