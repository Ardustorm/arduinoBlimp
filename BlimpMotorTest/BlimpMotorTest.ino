#include <Servo.h> 


//Pins that are connected to the H-Bridge
const int motorPin1 = 0;
const int motorPin2 = 1;

//Servos and their respective pins
Servo yawServo;
const int yawServoPin = 5;
Servo pitchServo;
const int pitchServoPin = 6;

void setup()
{
  yawServo.attach(yawServoPin);

  pinMode(motorPin1, OUTPUT); // set up for h bridge pin connection
  pinMode(motorPin2, OUTPUT);
}

void loop()
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
      digitalWrite(motorPin1, HIGH);
      Serial.print(" MOTOR ON ");
    }
    
    if(ByteReceived == '0' ) // turns off fan
    {
      digitalWrite(motorPin1, LOW);
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

