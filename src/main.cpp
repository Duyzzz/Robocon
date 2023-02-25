#include<Arduino.h>
#include <PS2X_lib.h> 
#include "moving.h"
#include <statusPs2.h>
#include <statusButtons.h>
#include <TimerOne.h>

Car rabbit;

void setUpRabbit(){
  rabbitSpeed = 120;
  rabbit.setTopLeftMotorPins(21, 20, 7);
  rabbit.setTopRightMotorPins(17, 16, 4);
  rabbit.setBottomLeftMotorPins(8, 10, 6);
  rabbit.setBottomRightMotorPins(14, 15, 5);
  rabbit.defineMotorPins();
}

void changeSpeed(){
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

  Timer1.initialize(20000);
  Timer1.attachInterrupt(changeSpeed);
  Timer1.start();
  Serial.print("start");
}
// test:



void loop()
{
  if(millis() - timeDelayVariable > 20){
  /*do something*/
  
  moving();
  timeDelayVariable = millis();
}
}

