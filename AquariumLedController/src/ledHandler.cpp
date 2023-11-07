#include <ledHandler.h>

void handleLed(LedType type){
    switch(type){
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
            digitalWrite(ledCPin,HIGH);
            break;
        }
        case (LedType::ledCOff):
        {
            digitalWrite(ledCPin,LOW);
            break;
        }
        case (LedType::ledWOn):
        {
            digitalWrite(ledWPin,HIGH);
            break;
        }
        case (LedType::ledWOff):
        {
            digitalWrite(ledWPin,LOW);
            break;
        }
        default:
            break;
    }

}

void ledSetup(void)
{
  pinMode(ledPin, OUTPUT); // Ustaw pin diody LED jako wyjście
  pinMode(ledCPin, OUTPUT); // Ustaw pin diody LED jako wyjście
  pinMode(ledWPin, OUTPUT); // Ustaw pin diody LED jako wyjście
  analogWrite(ledPin, LOW);
  digitalWrite(ledCPin, LOW);
  digitalWrite(ledWPin, LOW); 
}

void sliderLed(LedType type, int value){
    if(type==LedType::allLed){
        analogWrite(ledPin, value);
        analogWrite(ledCPin, value);
        analogWrite(ledWPin, value);
    }
    else if(type==LedType::LedC){
        analogWrite(ledCPin, value);
    }
    else if(type==LedType::LedW){
        analogWrite(ledWPin, value);
    }
}

void colorTemperatureLed(int value){
    switch (value)
    {
        case(2700):
        {
            analogWrite(ledWPin, 255);
            analogWrite(ledCPin, 0);
            break;
        }
        case(3000):
        {
            analogWrite(ledWPin, 255);
            analogWrite(ledCPin, 50);
            break;
        }
        case(3500):
        {
            analogWrite(ledWPin, 255);
            analogWrite(ledCPin, 140);
            break;
        }
        case(4000):
        {
            analogWrite(ledWPin, 255);
            analogWrite(ledCPin, 255);
            break;
        }
        case(4500):
        {
            analogWrite(ledWPin, 140);
            analogWrite(ledCPin, 255);
            break;
        }
        case(5000):
        {
            analogWrite(ledWPin, 89);
            analogWrite(ledCPin, 255);
            break;
        }
        case(5500):
        {
            analogWrite(ledWPin, 48);
            analogWrite(ledCPin, 255);
            break;
        }
        case(6000):
        {
            analogWrite(ledWPin, 20);
            analogWrite(ledCPin, 255);break;
        }
        case(6500):
        {
            analogWrite(ledWPin, 0);
            analogWrite(ledCPin, 255);
            break;
        }
        default:
            break;
    }
}