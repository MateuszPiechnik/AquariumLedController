#include <handleLed.h>

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
  analogWrite(ledPin, 254);
  digitalWrite(ledCPin, LOW);
  digitalWrite(ledWPin, LOW); 
}