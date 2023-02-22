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
        bool Status;
        unsigned long TimeDelay;
        unsigned int IntNumber;
    public:
        Button(unsigned int intNumber, unsigned long timeDelay = 0, bool status = false){
            IntNumber = intNumber;
            Status = status;
            TimeDelay = timeDelay;
        }
        bool checkIfPress(){
            return ps2x.Button(IntNumber);
        }
        void determineStatus(){
            if(checkIfPress() && Status == false){
                Status = true;
                TimeDelay = millis();
            }
            if(millis() - TimeDelay > 20 && checkIfPress() == 0 && Status == true){
                Status = false;
            }
        }
        bool callStatus(){
            determineStatus();
            return Status;
        }

};