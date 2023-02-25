#include <Arduino.h>

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




