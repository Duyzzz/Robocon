#include <Arduino.h>

class Motor{
    public:
    Motor (unsigned char upPin, unsigned char downPin, unsigned char speedPin){
        UpPin = upPin;
        DownPin = downPin;
        SpeedPin = speedPin;
    }
    void defineMotor (unsigned char upPin, unsigned char downPin, unsigned char speedPin){
        UpPin = upPin;
        DownPin = downPin;
        SpeedPin = speedPin;
    }
    void setSpeed(unsigned char speed){
        analogWrite(SpeedPin, speed);
    }
    void setStatus( char direction){
        if(direction == 1) {
            digitalWrite(DownPin, 0);
            digitalWrite(UpPin, 1);
        } else if(direction == -1){
            digitalWrite(UpPin, 0);
            digitalWrite(DownPin, 1);
        } else{
            analogWrite(SpeedPin, 0);
        }
    }
    void definePin(){
      pinMode(UpPin, OUTPUT);
      pinMode(DownPin, OUTPUT);
      pinMode(SpeedPin, OUTPUT);
    }
    private:
    unsigned char UpPin;
    unsigned char DownPin;
    unsigned char SpeedPin;
};


unsigned char speed(short x, short y){
  x = x - 127;
  y = 127 - y;
  if(abs(x) > abs(y)) return map(abs(x), 0, 128, 0, 255);
  else return map(abs(y), 0, 128, 0, 255);
}

unsigned char direction(short x, short y){
  x = x - 127;
  y = -y + 127;
  if(x*x + y*y <= 100) return 1; // 1 for standing still
  else {
    if((y > - x) && (x < y)) return 2; // 2 for moving forward
    else if((x > y) && (y > - x)) return 3; // 3 for moving right
    else if((x > y) && (y < -x)) return 4; // 4 for moving backward
    else if((x < y) && (y < -x)) return 5; // 5 for moving left
    else return 1;
  }
}
/*class Car {
  private:
  Motor topLeftMotor;
  Motor topRightMotor;
  Motor bottomLeftMotor;
  Motor bottomRightMotor;
  public:
  
};*/



void moveRight(int speed){
  topLeftMotor.setStatus(-1);
  bottomLeftMotor.setStatus(1);
  topRightMotor.setStatus(1);
  bottomRightMotor.setStatus(-1);
  topLeftMotor.setSpeed(speed);
  topRightMotor.setSpeed(speed);
  bottomLeftMotor.setSpeed(speed);
  bottomRightMotor.setSpeed(speed);
}
void moveLeft(int speed){
  topLeftMotor.setStatus(1);
  bottomLeftMotor.setStatus(-1);
  topRightMotor.setStatus(-1);
  bottomRightMotor.setStatus(1);
  topLeftMotor.setSpeed(speed);
  topRightMotor.setSpeed(speed);
  bottomLeftMotor.setSpeed(speed);
  bottomRightMotor.setSpeed(speed);
}
void moveForward(int speed){
  topLeftMotor.setStatus(1);
  bottomLeftMotor.setStatus(1);
  topRightMotor.setStatus(1);
  bottomRightMotor.setStatus(1);
  topLeftMotor.setSpeed(speed);
  topRightMotor.setSpeed(speed);
  bottomLeftMotor.setSpeed(speed);
  bottomRightMotor.setSpeed(speed);
}
void moveBackward(int speed){
  topLeftMotor.setStatus(-1);
  bottomLeftMotor.setStatus(-1);
  topRightMotor.setStatus(-1);
  bottomRightMotor.setStatus(-1);
  topLeftMotor.setSpeed(speed);
  topRightMotor.setSpeed(speed);
  bottomLeftMotor.setSpeed(speed);
  bottomRightMotor.setSpeed(speed);
}
// moving so slowly can help us do everything exactly.
void moveSlowLeft(){
  topLeftMotor.setStatus(1);
  bottomLeftMotor.setStatus(-1);
  topRightMotor.setStatus(-1);
  bottomRightMotor.setStatus(1);
  topLeftMotor.setSpeed(80);
  topRightMotor.setSpeed(80);
  bottomLeftMotor.setSpeed(80);
  bottomRightMotor.setSpeed(80);
}
void moveSlowRight(){
  topLeftMotor.setStatus(-1);
  bottomLeftMotor.setStatus(1);
  topRightMotor.setStatus(1);
  bottomRightMotor.setStatus(-1);
  topLeftMotor.setSpeed(80);
  topRightMotor.setSpeed(80);
  bottomLeftMotor.setSpeed(80);
  bottomRightMotor.setSpeed(80);
}
void moveSlowForward(){
  topLeftMotor.setStatus(1);
  bottomLeftMotor.setStatus(1);
  topRightMotor.setStatus(1);
  bottomRightMotor.setStatus(1);
  topLeftMotor.setSpeed(80);
  topRightMotor.setSpeed(80);
  bottomLeftMotor.setSpeed(80);
  bottomRightMotor.setSpeed(80);
}
void moveSlowBackward(){
  topLeftMotor.setStatus(-1);
  bottomLeftMotor.setStatus(-1);
  topRightMotor.setStatus(-1);
  bottomRightMotor.setStatus(-1);
  topLeftMotor.setSpeed(80);
  topRightMotor.setSpeed(80);
  bottomLeftMotor.setSpeed(80);
  bottomRightMotor.setSpeed(80);
}
void standStill(){
  topLeftMotor.setSpeed(0);
  topRightMotor.setSpeed(0);
  bottomLeftMotor.setSpeed(0);
  bottomRightMotor.setSpeed(0);
}
void turnLeftDrection(){
  
}
void getDirectionAndMove(unsigned char x, unsigned char y, short carSpeed){
  unsigned char directionValue = direction(x, y);
  switch (directionValue)
  {
  case 1: standStill();
    break;
  case 2: moveForward(carSpeed);
    break;
  case 3: moveRight(carSpeed);
    break;
  case 4: moveBackward(carSpeed);
    break;
  case 5: moveLeft(carSpeed);
    break;
  default:
    standStill();
    break;
  }
}

