#include <Servo.h> 


//Pins that are connected to the H-Bridge
const int motorPin1 = 0;
const int motorPin2 = 1;

//Servos and their respective pins
Servo yawServo;
const int yawServoPin = 5;
Servo pitchServo;
const int pitchServoPin = 6;

//Speed and location variables for servos and motor
int motorSpeed = 0;
int yawPositon = 90;

void setup()
{
  Serial.begin(9600);
  yawServo.attach(yawServoPin);

  pinMode(motorPin1, OUTPUT); // set up for h bridge pin connection
  pinMode(motorPin2, OUTPUT);

  Serial.println("Code Starts now");
  Serial.flush();
}

void loop()
{
  //characterControl();   //Original Control scheme using letters to control motor/servo
  numberControl();


}

void numberControl()
{

  Serial. println("Enter Motor Speed (-250 to 250), then press enter:");
  while(Serial.available() == 0);   // Wait here until input buffer has a character
  motorSpeed = Serial.parseInt();
  Serial.print("motorSpeed = "); Serial.println(motorSpeed,DEC);
  Serial.print("Yaw Position = "); Serial.println(yawPositon,DEC);

  Serial. println("Enter Servo Position (0 to 180), then press enter:");
  while(Serial.available() == 0);   // Wait here until input buffer has a character
  yawPositon = Serial.parseInt();
  Serial.print("motorSpeed = "); Serial.println(motorSpeed,DEC);
  Serial.print("Yaw Position = "); Serial.println(yawPositon,DEC);


  drive(motorSpeed);
  steer(yawPositon,0);
  
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

