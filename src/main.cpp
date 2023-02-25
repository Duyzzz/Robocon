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

short speedValue = 120;


Car rabbit;

void setUpRabbit(){
  rabbitSpeed = 120;
  timeDelaySpeed = millis();
  rabbit.setTopLeftMotorPins(21, 20, 7);
  rabbit.setTopRightMotorPins(17, 16, 4);
  rabbit.setBottomLeftMotorPins(8, 10, 6);
  rabbit.setBottomRightMotorPins(14, 15, 5);
  rabbit.defineMotorPins();
}

SimpleTimer timer;
void changeSpeed(){
    ps2x.read_gamepad(false, vibrate);
    vibrate = ps2x.Analog(PSAB_BLUE);
  if (ps2x.NewButtonState())
    {
      if(ps2x.ButtonPressed(PSB_GREEN)){
          rabbitSpeed = rabbitSpeed + 10;
          if(rabbitSpeed > 255) rabbitSpeed = 250;
          Serial.print("Toc do hien tai: ");
          Serial.println(rabbitSpeed);
        }
      if(ps2x.ButtonPressed(PSB_BLUE)){
          rabbitSpeed = rabbitSpeed - 10;
          if(rabbitSpeed <= 0) rabbitSpeed = 0;

          Serial.print("Toc do hien tai: ");
          Serial.println(rabbitSpeed);
        }
    }
}

unsigned long timeDelayVariable = 0;

void moving(){
    if(error == 1)
    return; 
  
    if(type == 2)
    {

    }
    else
    {
      ps2x.read_gamepad(false, vibrate);
      vibrate = ps2x.Analog(PSAB_BLUE);
    // will be TRUE if any button changes state (on to off, or off to on)
    
      if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
      {
        rabbit.run(ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY), rabbitSpeed);
      }
    }
}

void setup()
{
  setUpRabbit();
  setupFunction();
  Serial.begin(57600);
  timeDelayVariable = millis();
  timer.setInterval(20, changeSpeed);
  timerSpeedStatus.setInterval(20, determineSpeedStatus);
  timerMoving.setInterval(20,moving);
  speedStatus = false;
  Serial.print("start");
}
// test:


void loop()
{
  timerSpeedStatus.run();
  if(speedStatus){
    /* scope nay de chinh toc do*/
    timer.run();
  }
  else {
    /*scope nay de cho robot chay*/
    timerMoving.run();
  }
  //  timerMoving.run();
  // timer.run();
  // buttonJustClick();
}

