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

Motor topLeftMotor(21, 20, 7);
Motor topRightMotor(17, 16, 4);
Motor bottomLeftMotor(18, 19, 6);
Motor bottomRightMotor(14, 15, 5);
void speedSet(){
  carSpeed = 123;
}
void definePinUsing(){
  topLeftMotor.definePin();
  topRightMotor.definePin();
  bottomLeftMotor.definePin();
  bottomRightMotor.definePin();
}
void setup()
{
  Serial.begin(57600);
  definePinUsing();
  setupFunction();
}


void loop()
{
  //getDirectionAndMove(ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY));
  Serial.print("x  =  ");
  Serial.print(ps2x.Analog(PSS_LX) - 127);
  Serial.print("   y =  ");
  Serial.print(127 - ps2x.Analog(PSS_LY));
  Serial.print("  speed: ");
  Serial.println(speed(ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY)));
  buttonJustClick();
}
