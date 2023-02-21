#include<Arduino.h>
#include <PS2X_lib.h>  //for v1.6
#include "moving.h"
#include <statusPs2.h>
/*
  right now, the library does NOT support hot pluggable controllers, meaning 
  you must always either restart your Arduino after you connect the controller, 
  or call config_gamepad(pins) again after connecting the controller.
*/
// create PS2 Controller Class
short carSpeed;

Car rabbit;

void setUpRabbit(){
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
}


void loop()
{
  carSpeed = 12;
  buttonJustClick();
}
