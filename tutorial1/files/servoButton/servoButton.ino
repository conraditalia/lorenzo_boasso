#include <Servo.h> 

Servo myservo;  // create object controller

const int buttonPin = 2;     // pin where I attach my button
const int servoPin = 9;      // pin where I attach my servo

int pos = 0;    // actual servo position 
int dir = 1;    // actual servo direction

int buttonState = 0;      // 0 unpressed, 1 pressed
 
void setup() 
{ 
  myservo.attach(servoPin);  // init servo
  pinMode(buttonPin, INPUT); // pin button is in input
} 
 
void loop() 
{ 
  buttonState = digitalRead(buttonPin); // read actual pin status
  if (buttonState != 0){  // if pressed
    if (dir == 1){
      for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(6);                       
      } 
    }else{
        for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
        {                                
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          delay(6);                       
        } 
    }
    dir *= -1;
  }
} 

