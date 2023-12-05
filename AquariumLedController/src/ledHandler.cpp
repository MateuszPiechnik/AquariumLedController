#include <ledHandler.h>

LedHandler::LedHandler(int pinLed, int pinLedC, int pinLedW) : ledPin(pinLed), ledCPin(pinLedC), ledWPin(pinLedW) {}

void LedHandler::ledSetup(){
    pinMode(ledPin, OUTPUT); 
    pinMode(ledCPin, OUTPUT); 
    pinMode(ledWPin, OUTPUT); 
    analogWrite(ledPin, LOW);
    digitalWrite(ledCPin, LOW);
    digitalWrite(ledWPin, LOW); 
}

void LedHandler::daySimulation(int actualTime, int previousTime, int sunriseTime, int sunsetTime)
{
    if (actualTime - previousTime != 0) // aktualizuj dane co minute
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
            int brightness = map(actualTime, 1500, sunsetTime, 255, 0);
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

void LedHandler::colorTemperatureLed(int value, int percentage){
    switch (value)
    {
    case (2700):
    {
        analogWrite(ledWPin, 255 * percentage / 100);
        analogWrite(ledCPin, 0);
        break;
    }
    case (3000):
    {
        analogWrite(ledWPin, 255 * percentage / 100);
        analogWrite(ledCPin, 50 * percentage / 100);
        break;
    }
    case (3500):
    {
        analogWrite(ledWPin, 255 * percentage / 100);
        analogWrite(ledCPin, 140 * percentage / 100);
        break;
    }
    case (4000):
    {
        analogWrite(ledWPin, 255 * percentage / 100);
        analogWrite(ledCPin, 255 * percentage / 100);
        break;
    }
    case (4500):
    {
        analogWrite(ledWPin, 140 * percentage / 100);
        analogWrite(ledCPin, 255 * percentage / 100);
        break;
    }
    case (5000):
    {
        analogWrite(ledWPin, 89 * percentage / 100);
        analogWrite(ledCPin, 255 * percentage / 100);
        break;
    }
    case (5500):
    {
        analogWrite(ledWPin, 48 * percentage / 100);
        analogWrite(ledCPin, 255 * percentage / 100);
        break;
    }
    case (6000):
    {
        analogWrite(ledWPin, 20 * percentage / 100);
        analogWrite(ledCPin, 255 * percentage / 100);
        break;
    }
    case (6500):
    {
        analogWrite(ledWPin, 0);
        analogWrite(ledCPin, 255 * percentage / 100);
        break;
    }
    default:
        break;
    }
}

void LedHandler::handleLed(LedType type)
{
    switch (type)
    {
    case (LedType::ledOn):
    {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledCPin, HIGH);
        digitalWrite(ledWPin, HIGH);
        break;
    }
    case (LedType::ledOff):
    {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledCPin, LOW);
        digitalWrite(ledWPin, LOW);
        break;
    }
    case (LedType::ledCOn):
    {
        digitalWrite(ledCPin, HIGH);
        break;
    }
    case (LedType::ledCOff):
    {
        digitalWrite(ledCPin, LOW);
        break;
    }
    case (LedType::ledWOn):
    {
        digitalWrite(ledWPin, HIGH);
        break;
    }
    case (LedType::ledWOff):
    {
        digitalWrite(ledWPin, LOW);
        break;
    }
    default:
        break;
    }
}

void LedHandler::sliderLed(LedType type, int value){
    if (type == LedType::allLed)
    {
        analogWrite(ledPin, value);
        analogWrite(ledCPin, value);
        analogWrite(ledWPin, value);
    }
    else if (type == LedType::LedC)
    {
        analogWrite(ledCPin, value);
    }
    else if (type == LedType::LedW)
    {
        analogWrite(ledWPin, value);
    }
}