#include <Arduino.h>

class Motor{
    public:
    Motor() = default;
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
  if(x*x + y*y <= 50*50*2) return 1; // 1 for standing still
  else {
    if((y > - x) && (x < y)) return 2; // 2 for moving forward
    else if((x > y) && (y > - x)) return 3; // 3 for moving right
    else if((x > y) && (y < -x)) return 4; // 4 for moving backward
    else if((x < y) && (y < -x)) return 5; // 5 for moving left
    else return 1;
  }
}
class Car {
  private:
    Motor TopLeftMotor;
    Motor TopRightMotor;
    Motor BottomLeftMotor;
    Motor BottomRightMotor;
  public:
    Car() = default; // define default constructor
    Car(Motor topLeftMotor, Motor topRightMotor, Motor bottomLeftMotor, Motor bottomRightMotor){
      TopLeftMotor = topLeftMotor;
      TopRightMotor = topRightMotor;
      BottomLeftMotor = bottomLeftMotor;
      BottomRightMotor = bottomRightMotor;
    }
    void setTopLeftMotorPins(unsigned char upPin, unsigned char downPin, unsigned char speedPin) {
      TopLeftMotor.defineMotor(upPin, downPin, speedPin);
    }
    void setTopRightMotorPins(unsigned char upPin, unsigned char downPin, unsigned char speedPin) {
      TopRightMotor.defineMotor(upPin, downPin, speedPin);
    }
    void setBottomLeftMotorPins(unsigned char upPin, unsigned char downPin, unsigned char speedPin) {
      BottomLeftMotor.defineMotor(upPin, downPin, speedPin);
    }
    void setBottomRightMotorPins(unsigned char upPin, unsigned char downPin, unsigned char speedPin) {
      BottomRightMotor.defineMotor(upPin, downPin, speedPin);
    }
    void defineMotorPins(){
      TopLeftMotor.definePin();
      TopRightMotor.definePin();
      BottomLeftMotor.definePin();
      BottomRightMotor.definePin();
    }
    void moveRight(int speed){
      TopLeftMotor.setStatus(-1);
      BottomLeftMotor.setStatus(1);
      TopRightMotor.setStatus(1);
      BottomRightMotor.setStatus(-1);
      TopLeftMotor.setSpeed(speed);
      TopRightMotor.setSpeed(speed);
      BottomLeftMotor.setSpeed(speed);
      BottomRightMotor.setSpeed(speed);
    }
    void moveLeft(int speed){
      TopLeftMotor.setStatus(1);
      BottomLeftMotor.setStatus(-1);
      TopRightMotor.setStatus(-1);
      BottomRightMotor.setStatus(1);
      TopLeftMotor.setSpeed(speed);
      TopRightMotor.setSpeed(speed);
      BottomLeftMotor.setSpeed(speed);
      BottomRightMotor.setSpeed(speed);
    }
    void moveForward(int speed){
      TopLeftMotor.setStatus(1);
      BottomLeftMotor.setStatus(1);
      TopRightMotor.setStatus(1);
      BottomRightMotor.setStatus(1);
      TopLeftMotor.setSpeed(speed);
      TopRightMotor.setSpeed(speed);
      BottomLeftMotor.setSpeed(speed);
      BottomRightMotor.setSpeed(speed);
    }
    void moveBackward(int speed){
      TopLeftMotor.setStatus(-1);
      BottomLeftMotor.setStatus(-1);
      TopRightMotor.setStatus(-1);
      BottomRightMotor.setStatus(-1);
      TopLeftMotor.setSpeed(speed);
      TopRightMotor.setSpeed(speed);
      BottomLeftMotor.setSpeed(speed);
      BottomRightMotor.setSpeed(speed);
    }

    void standStill(){
      TopLeftMotor.setSpeed(0);
      TopRightMotor.setSpeed(0);
      BottomLeftMotor.setSpeed(0);
      BottomRightMotor.setSpeed(0);
    } 
  void run(unsigned char x, unsigned char y, short carSpeed){
    unsigned char directionValue = direction(x, y);
    switch (directionValue)
    {
    case 1: {
      Serial.println("standing still");
      standStill();
    }
      break;
    case 2: {
      Serial.println("moving forward with");
      moveForward(carSpeed);
      break;
    }
    case 3:{
      Serial.println("moving right with");
      moveRight(carSpeed);
      break;
      }
    case 4: {
      Serial.println("moving back with");
      moveBackward(carSpeed);
      break;
      }
    case 5: {
      Serial.println("moving left with");
      moveLeft(carSpeed);
      break;
      }
    default:
      standStill();
      break;
    }
    delay(20);
  }
};



