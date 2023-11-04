#include <ledHandler.h>

void handleLed(LedType type){
    switch(type){
        case (LedType::ledOn):
        {
            digitalWrite(ledPin, LOW);
            break;
        }
        case (LedType::ledOff):
        {
            digitalWrite(ledPin, HIGH);
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
    }
    else if(type==LedType::LedC){
        analogWrite(ledCPin, value);
    }
    else if(type==LedType::LedW){
        analogWrite(ledWPin, value);
    }
}