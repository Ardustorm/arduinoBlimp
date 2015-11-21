#include <Servo.h> 


//Pins that are connected to the H-Bridge
const int motorPinL1 = 0;
const int motorPinL2 = 1;
const int motorPinR1 = 5;
const int motorPinR2 = 6;

//Servo and its respective pin
Servo angleServo;
const int angleServoPin = 5;


//Speed and location variables for servos and motor
int motorSpeedL = 0;
int motorSpeedR = 0;
int anglePosition = 90;

void setup()
{
  Serial.begin(9600);
  angleServo.attach(angleServoPin);

  pinMode(motorPinL1, OUTPUT); // set up for h bridge pin connection
  pinMode(motorPinL2, OUTPUT);
  pinMode(motorPinR1, OUTPUT); // set up for h bridge pin connection
  pinMode(motorPinR2, OUTPUT);

  Serial.println("Code Starts now");
  Serial.flush();
}

void loop()
{
  //characterControl();   //Original Control scheme using letters to control motor/servo
  numberControl();
  Serial.print("LEFT motorSpeed = "); Serial.println(motorSpeedL,DEC);

  Serial.print("Right motorSpeed = "); Serial.println(motorSpeedR,DEC);
  Serial.print("Angle Position = "); Serial.println(anglePosition,DEC);


}

void numberControl()
{

  Serial. println("Enter LEFT Motor Speed (-250 to 250), then press enter:");
  while(Serial.available() == 0);   // Wait here until input buffer has a character
  motorSpeedL = Serial.parseInt();
  Serial. println("Enter Right Motor Speed (-250 to 250), then press enter:");
  while(Serial.available() == 0);   // Wait here until input buffer has a character
  motorSpeedR = Serial.parseInt();

  Serial. println("Enter Servo Position (0 to 180), then press enter:");
  while(Serial.available() == 0);   // Wait here until input buffer has a character
  anglePosition = Serial.parseInt();
  Serial.print("motorSpeed left= "); Serial.println(motorSpeedL,DEC);
  Serial.print("motorSpeed Right= "); Serial.println(motorSpeedR,DEC);
  Serial.print("Yaw Position = "); Serial.println(anglePosition,DEC);


  drive(motorSpeedL,motorSpeedR,anglePosition);
  
}
void characterControl()
{
    if (Serial.available() > 0)
  {
    int ByteReceived = Serial.read(); // reads from console
    Serial.print(ByteReceived);   // prints input back to terminal
    Serial.print("        ");      
    Serial.print(ByteReceived, HEX);
    Serial.print("       ");     
    Serial.print(char(ByteReceived));
    
    if(ByteReceived == '1' ) // Inputting 1 turns on fan
    {
      digitalWrite(motorPinL1, HIGH);
      Serial.print(" MOTOR ON ");
    }
    
    if(ByteReceived == '0' ) // turns off fan
    {
      digitalWrite(motorPinL1, LOW);
      Serial.print(" MOTOR OFF ");
    }

    if (ByteReceived == 'c' ) // brings to center
    {
      Serial.print(" SERVO TURNED TO CENTER ");
      steer(90, 0);
    }

    if (ByteReceived == 'r') // rotates rightmost
    {
      Serial.print(" SERVO TURNED RIGHT ");
      steer(180, 0);
    }

    if (ByteReceived == 'l') // rotates leftmost
    {
      Serial.print(" SERVO TURNED LEFT ");
      steer(0, 0);
    }
    
    Serial.println();    // End the line

  // END Serial Available
  }
}

void drive(int speedL, int speedR, int angle)     //-250 to 250 for speed, 0 to 180 for angle
{
  if(speedL >= 0)                     //Left motor control
  {
    analogWrite(motorPinL1, speedL);
    analogWrite(motorPinL2, 0);
  }
  else if(speedL < 0)
  {
    analogWrite(motorPinL2, speedL);
    analogWrite(motorPinL1, 0);
  }
  
  if(speedR >= 0)                     //Right motor control
  {
    analogWrite(motorPinR1, speedR);
    analogWrite(motorPinR2, 0);
  }
  else if(speedR < 0)
  {
    analogWrite(motorPinR2, speedR);
    analogWrite(motorPinR1, 0);
  }
  angleServo.write(angle);
}


//This is outdated and will be removed soon: v
void steer(int yaw, int pitch)
{
//  yawServo.write(yaw);
  //pitchServo.write(pitch);
}

