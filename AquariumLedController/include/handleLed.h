#include <Arduino.h>
#include <string>

const int ledPin = D4;
const int ledCPin = D3;
const int ledWPin = D2;

enum LedType {
    ledOn,
    ledOff,
    ledCOn,
    ledCOff,
    ledWOn,
    ledWOff
};

void handleLed(LedType type);
void ledSetup(void);