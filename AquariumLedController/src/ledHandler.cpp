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

void LedHandler::daySimulation(int actualTime, int sunriseTime, int sunsetTime)
{
    if (actualTime - previousTime != 0) // aktualizuj dane co minute
    {
        Serial.print("Aktualna godzina: ");
        Serial.println(actualTime);
        if (actualTime < sunriseTime || actualTime > sunsetTime)
        {
            digitalWrite(ledWPin, LOW);
            digitalWrite(ledCPin, LOW);
            Serial.println("Diody wyłączone - panuej zmrok");
        }
        else if (actualTime == sunriseTime || actualTime == sunsetTime)
        {
            analogWrite(ledWPin, 1);
            digitalWrite(ledCPin, LOW);
            Serial.println("Wartość wypełnienia diody ciepłej : 1");
            Serial.println("Wartość wypełnienia diody zimnej : 0");
        }
        else if (actualTime == 1200)
        {
            digitalWrite(ledWPin, LOW);
            digitalWrite(ledCPin, HIGH);
            Serial.println("Wartość wypełnienia diody ciepłej : 0");
            Serial.println("Wartość wypełnienia diody zimnej : 255");
        }
        else if (actualTime > sunriseTime && actualTime < 800)
        {
            int brightness = map(actualTime, sunriseTime, 800, 1, 255);
            analogWrite(ledWPin, brightness);
            digitalWrite(ledCPin, LOW);
            Serial.print("Wartość wypełnienia diody ciepłej: ");
            Serial.println(brightness);
            Serial.println("Wartość wypełnienia diody zimnej: 0");
        }
        else if (actualTime > 800 && actualTime < 900)
        {
            int brightness = map(actualTime, 800, 900, 0, 127);
            int brightnessW = map(actualTime, 800, 900, 255, 127);
            analogWrite(ledWPin, brightnessW);
            analogWrite(ledCPin, brightness);
            Serial.print("Wartość wypełnienia diody ciepłej: ");
            Serial.println(brightnessW);
            Serial.print("Wartość wypełnienia diody zimnej: ");
            Serial.println(brightness);
        }
        else if (actualTime > 900 && actualTime < 1200)
        {
            int brightness = map(actualTime, 900, 1200, 127, 0);
            int brightnessC = map(actualTime, 900, 1200, 127, 255);
            analogWrite(ledCPin, brightnessC);
            analogWrite(ledWPin, brightness);
            Serial.print("Wartosc wypelnienia diody cieplej: ");
            Serial.println(brightness);
            Serial.print("Wartosc wypelnienia diody zimnej:");
            Serial.println(brightnessC);
        }
        else if (actualTime > 1200 && actualTime < 1400)
        {
            int brightness = map(actualTime, 1200, 1500, 0, 127);
            int brightnessC = map(actualTime, 1200, 1500, 255, 127);
            analogWrite(ledCPin, brightnessC);
            analogWrite(ledWPin, brightness);
            Serial.print("Wartosc wypelnienia diody cieplej: ");
            Serial.println(brightness);
            Serial.print("Wartosc wypelnienia diody zimnej:");
            Serial.println(brightnessC);
        }
        else if (actualTime > 1400 && actualTime < 1500)
        {
            int brightness = map(actualTime, 1400, 1500, 127, 255);
            int brightnessC = map(actualTime, 1400, 1500, 127, 0);
            analogWrite(ledCPin, brightnessC);
            analogWrite(ledWPin, brightness);
            Serial.print("Wartość wypełnienia diody ciepłej:");
            Serial.println(brightness);
            Serial.print("Wartość wypełnienia diody zimnej:");
            Serial.println(brightnessC);
        }
        else if (actualTime > 1500 && actualTime < sunsetTime)
        {
            int brightness = map(actualTime, 1500, sunsetTime, 255, 0);
            analogWrite(ledWPin, brightness);
            digitalWrite(ledCPin, LOW);
            Serial.print("Wartość wypełnienia diody ciepłej: ");
            Serial.println(brightness);
            Serial.println("Wartość wypełnienia diody zimnej: 0");
        }
        else if (actualTime == 900 || actualTime == 1500)
        {
            analogWrite(ledWPin, 127);
            digitalWrite(ledCPin, 127);
            Serial.println("Wartość wypełnienia diody ciepłej: 127");
            Serial.println("Wartość wypełnienia diody zimnej: 127");
        }
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