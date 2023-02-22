#include <Arduino.h>

const char switchSpeedStatusButton = 19; // default
const char increaseButton = 11;
const char decreaseButton = 9;
short rabbitSpeed;
bool speedStatus = false;
unsigned long timeDelaySpeed = 0;

void determineSpeedStatus(){
    if(digitalRead(switchSpeedStatusButton) == 0 && speedStatus == false){
    speedStatus = true;
    timeDelaySpeed = millis();
  }
  if(millis() - timeDelaySpeed > 20 && digitalRead(switchSpeedStatusButton) == 1 && speedStatus == true){
    speedStatus = false;
  }
}


class Button{
    private:
        unsigned char DigitalPin;
        bool Status;
        unsigned long TimeDelay;
    public:
        Button(unsigned char digitalPin, unsigned long timeDelay = 0, bool status = false){
            DigitalPin = digitalPin;
            Status = status;
            TimeDelay = timeDelay;
        }
        void determineStatus(){
            if(digitalRead(DigitalPin) == 0 && Status == false){
                Status = true;
                TimeDelay = millis();
            }
            if(millis() - TimeDelay > 20 && digitalRead(DigitalPin) == 1 && Status == true){
                Status = false;
            }
        }

};