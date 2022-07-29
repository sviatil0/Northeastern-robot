//MAIN ALGORITHM  

// FRONT ULTRASONIC
const int ECHO_FRONT = 5;
const int TRIGGER_FRONT = 6;

// RIGHT ULTRASONIC
const int ECHO_RIGHT = A1;
int TRIGGER_RIGHT = A0;

// LEFT ULTRASONIC
const int ECHO_LEFT = 3;
const int TRIGGER_LEFT = 4;


const int switchPin = 7;   

//Ultrasonic code
float getDistance(int trigPin, int echoPin)
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}




//Motors code



//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
void brake(){
  rightMotor(0);
  leftMotor(0);
}

 void turnLeft(){
  rightMotor(-150); // Turn on right motor clockwise medium power (motorPower = 150) 
  leftMotor(150); // Turn on left motor counter clockwise medium power (motorPower = 150) 
 // delay(250);       // for 1000 ms.
 delay(50);
  brake();    // brake() motors
 }
 void turnRight(){
  // drive forward -- instead of using motors.drive(); Here is another way.
  rightMotor(150); // Turn on right motor clockwise medium power (motorPower = 150) 
  leftMotor(-150); // Turn on left motor counter clockwise medium power (motorPower = 150)
 // delay(400);       // for 1000 ms.
 delay(100);
  brake();     // brake() motors
}

void goStraight1(){
   rightMotor(178); // Turn on right motor clockwise medium power (motorPower = 150) 
   leftMotor(108); // Turn on left motor counter clockwise medium power (motorPower = 150)
   
  delay(1000);       // for 1000 ms.
  brake();     // brake() motors
}

void goStraight2(){
   rightMotor(178); // Turn on right motor clockwise medium power (motorPower = 150) 
   leftMotor(120); // Turn on left motor counter clockwise medium power (motorPower = 150)
   
  delay(1000);       // for 1000 ms.
  brake();     // brake() motors
}



void setup(){

 

  //Setup for the FRONT Sensor
  pinMode(TRIGGER_FRONT, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(ECHO_FRONT, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

 //Setup for the LEFT Sensor

  pinMode(TRIGGER_LEFT, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(ECHO_LEFT, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

 //Setup for the RIGHT Sensor

pinMode(TRIGGER_RIGHT, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(ECHO_RIGHT, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

 
Serial.begin(9600);
delay(250);

}

void loop(){

 

  
if (digitalRead(switchPin) == LOW){
 goStraight1();
 delay(200);
goStraight2();
float distanceFront = getDistance( TRIGGER_FRONT, ECHO_FRONT);
delay(50);
float distanceRight = getDistance( TRIGGER_RIGHT, ECHO_RIGHT);
delay(50);
float distanceLeft = getDistance( TRIGGER_LEFT, ECHO_LEFT);

if(distanceFront <= 35){
  if (distanceLeft > distanceRight){
    //turn left
    
    Serial.println("Turning LEFT");
    
    while(true){
      turnLeft();
      delay(50);
      distanceFront = getDistance( TRIGGER_FRONT, ECHO_FRONT);
      if (distanceFront >35) break;
    }
   
  }
  else if (distanceRight > distanceLeft){
    // turn right
 
    Serial.println("Turning RIGHT");

      while(true){
      turnRight();
      delay(50);
      distanceFront = getDistance( TRIGGER_FRONT, ECHO_FRONT);
      if (distanceFront >35)break;
    }
  }
  
}

Serial.println("Going Straight");
 goStraight1();
  delay(200);
goStraight2();
//go straight 

}

} 
