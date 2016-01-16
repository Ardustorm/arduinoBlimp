#include <Servo.h>


//Pins that are connected to the H-Bridge
const int motorPinL1 = 0;
const int motorPinL2 = 1;
const int motorPinR1 = 5;
const int motorPinR2 = 6;

//Servo and its respective pin
Servo angleServo;
const int angleServoPin = 3;

//Serial Control Var
char command;
int number;

//Speed and location variables for servos and motor
int motorSpeedL = 0;
int motorSpeedR = 0;
int anglePosition = 90;

void setup() {
  Serial.begin(9600);
  angleServo.attach(angleServoPin);

  pinMode(motorPinL1, OUTPUT); // set up for h bridge pin connection
  pinMode(motorPinL2, OUTPUT);
  pinMode(motorPinR1, OUTPUT); // set up for h bridge pin connection
  pinMode(motorPinR2, OUTPUT);
  Serial.println("Commands: l(speed), r(speed),a(angle),s");
  delay(1000);
  Serial.println("Code Starts now");
  Serial.flush();
}


void loop() {
  // put your main code here, to run repeatedly:

}


bool processCommand(char & command, int & number)
{
  // Each state is defined by its command

  if (command == 'l')
  {
    //Sets the left motor on
    if (number >= 0)                    //Left motor control
    {
      analogWrite(motorPinL1, number);
      analogWrite(motorPinL2, 0);
    }
    else if (number < 0)
    {
      analogWrite(motorPinL2, number);
      analogWrite(motorPinL1, 0);
    }
  }
  if (command == 'r')
  {
  if (number >= 0)                    //Right motor control
    {
      analogWrite(motorPinR1, number);
      analogWrite(motorPinR2, 0);
    }
    else if (number < 0)
    {
      analogWrite(motorPinR2, number);
      analogWrite(motorPinR1, 0);
    }
      

  }
  if (command == 'a')
  {
    angleServo.write(number);
    
  }
  if (command == 's')
  {
    drive(0,0,0);
  }
}










int getCommand(char & command, int & number)
{
  static int returnVal;
  if (Serial.available())
  {
    command = Serial.read();
    returnVal = 1;
    if (command == 'l' || command == 'r' || command == 'a')
    {
      number = Serial.parseInt();
    }
    else
    {
      number = 0;
    }
  }
  else
  {
    command = '\0';
    number = 0;
    returnVal = 0;
  }
  return returnVal;
}





void drive(int speedL, int speedR, int angle)     //-250 to 250 for speed, 0 to 180 for angle
{
  if (speedL >= 0)                    //Left motor control
  {
    analogWrite(motorPinL1, speedL);
    analogWrite(motorPinL2, 0);
  }
  else if (speedL < 0)
  {
    analogWrite(motorPinL2, speedL);
    analogWrite(motorPinL1, 0);
  }

  if (speedR >= 0)                    //Right motor control
  {
    analogWrite(motorPinR1, speedR);
    analogWrite(motorPinR2, 0);
  }
  else if (speedR < 0)
  {
    analogWrite(motorPinR2, speedR);
    analogWrite(motorPinR1, 0);
  }
  angleServo.write(angle);
}


