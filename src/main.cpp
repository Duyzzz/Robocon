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
  rabbit.setBottomLeftMotorPins(18, 19, 6);
  rabbit.setBottomRightMotorPins(14, 15, 5);
  rabbit.defineMotorPins();
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


void loop()
{
  determineSpeedStatus();
  if(speedStatus){
    if(millis() - timeDelaySpeed > 20 && digitalRead(increaseButton == 0)){
      /*testing time*/
    }
  }
  buttonJustClick();
}
