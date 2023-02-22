#include<Arduino.h>
#include <PS2X_lib.h>  //for v1.6
#include "moving.h"
#include <statusPs2.h>
#include <statusButtons.h>
/*
  right now, the library does NOT support hot pluggable controllers, meaning 
  you must always either restart your Arduino after you connect the controller, 
  or call config_gamepad(pins) again after connecting the controller.
*/
// create PS2 Controller Class

short speedValue = 123;

void changeSpeed(bool increaseOrDecrease/*true is increase false is decrease*/){
  if(increaseOrDecrease) speedStatus = speedStatus + 10;
  else speedStatus = speedStatus - 10;
}
Car rabbit;

void setUpRabbit(){
  rabbitSpeed = 123;
  timeDelaySpeed = millis();
  rabbit.setTopLeftMotorPins(21, 20, 7);
  rabbit.setTopRightMotorPins(17, 16, 4);
  rabbit.setBottomLeftMotorPins(8, 10, 6);
  rabbit.setBottomRightMotorPins(14, 15, 5);
  rabbit.defineMotorPins();
}

void moving(){
  if(error == 1)
    return; 
  
  if(type == 2)
  {

  }
  else
  {
    // DualShock Controller
    // read controller and set large motor to spin at 'vibrate' speed
    ps2x.read_gamepad(false, vibrate);

    // this will set the large motor vibrate speed based on how hard you press the blue (X) button
    vibrate = ps2x.Analog(PSAB_BLUE);
    
    // will be TRUE if any button changes state (on to off, or off to on)
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
    {
      rabbit.run(ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY), 123);
    }
  }

delay(20);
}

void setup()
{
  setUpRabbit();
  Serial.begin(57600);
  setupFunction();

  pinMode(increaseButton, INPUT_PULLUP);
  pinMode(decreaseButton, INPUT_PULLUP);
  pinMode(switchSpeedStatusButton, INPUT_PULLUP);
}
// test:
Button L3(PSB_RED);

void loop()
{
  // determineSpeedStatus();
  // if(speedStatus){
  //   if(millis() - timeDelaySpeed > 20 && digitalRead(increaseButton == 0)){
  //     /*testing time*/
  //   }
  // }
  // if(L3.callStatus()){
  //   Serial.print("true");
  // }
  moving();
}
