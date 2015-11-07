#include <Servo.h> 


//Pins that are connected to the H-Bridge
const int motorPin1 = 1;
const int motorPin2 = 2;

//Servos and their respective pins
Servo yawServo;
const int yawServoPin = 5;
Servo pitchServo;
const int pitchServoPin = 6;

void setup()
{
  yawServo.attach(yawServoPin);
}

void loop()
{
  // put your   main code here, to run repeatedly:
  drive(250);
  delay(1000);

}


void drive(int speed)     //-250 to 250
{
  if(speed >= 0)
  {
    analogWrite(motorPin1, speed);
    analogWrite(motorPin2, 0);
  }
  else if(speed < 0)
  {
    analogWrite(motorPin2, speed);
    analogWrite(motorPin1, 0);
  }
}

void steer(int yaw, int pitch)
{
  yawServo.write(yaw);
  pitchServo.write(pitch);
}

