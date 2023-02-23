#include <Arduino.h>

const char switchSpeedStatusButton = PSB_SELECT; // default
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
        unsigned short HexOfButton;
    public:
        Button(unsigned int intNumber, unsigned long timeDelay = 0, bool status = false){
            HexOfButton = intNumber;
            Status = status;
            TimeDelay = timeDelay;
        }
        bool checkIfPress(){
            return ps2x.Button(HexOfButton);
        }
        bool callStatus(){
            if(checkIfPress() && Status == false){
                Status = true;
                TimeDelay = millis();
            }
            if(millis() - TimeDelay > 20 && checkIfPress() == 0 && Status == true){
                Status = false;
            }
            /* Nếu nhấn nút biến status sẽ chuển thành true */
            return Status;
        }

};