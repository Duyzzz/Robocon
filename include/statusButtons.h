#include <Arduino.h>
#include <SimpleTimer.h>

class Button{
    private:
        bool Status;
        unsigned long TimeDelay;
        unsigned int HexOfButton;
    public:
        Button(unsigned int hexOfButton, unsigned long timeDelay = 0, bool status = false){
            HexOfButton = hexOfButton;
            Status = status;
            TimeDelay = timeDelay;
        }
        boolean checkIfPress(){
            return ps2x.ButtonPressed(HexOfButton);
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

Button switchChangeStatusSpeed(PSB_SELECT);
Button increaseSpeed(PSB_GREEN); /* bookkkkkkk*/
Button decreaseSpeed(PSB_BLUE);

unsigned long timeDelaySpeed = 0;
bool speedStatus = false;

SimpleTimer timerSpeedStatus;

void determineSpeedStatus(){
    if(ps2x.NewButtonState()){
        ps2x.read_gamepad(false, vibrate);
        vibrate = ps2x.Analog(PSAB_BLUE);
        if(ps2x.Button(PSB_SELECT)){
            speedStatus = !speedStatus;
            if(speedStatus){
                Serial.println("dang o mode chinh sua toc do");
            }else {
                Serial.println("dang o mode di chuyen");
            }
        }
    }
}

