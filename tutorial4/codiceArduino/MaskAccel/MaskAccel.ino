#include <Servo.h> 

Servo myservoL;  // create servo controller
Servo myservoR;

const int servoPinL = 10;      // pin where I attach servo
const int servoPinR = 9;      // pin where I attach servo

const int eyePinL = 6;       // pin where I attach the leds 
const int eyePinR = 5;       // pin where I attach the leds 

const int accX = A0; // pin where I attach the x analog from accelerometer 
int accValue;

int eyeFade = 0;
int pos = 0;    // actual servo position 
int dir = 1;    // actual servo direction

void setup() 
{   
  myservoL.write( leftServoPos(0) ); 
  myservoR.write( rightServoPos(0) );

  pinMode(eyePinL, OUTPUT); // pin button is in output
  pinMode(eyePinR, OUTPUT); // pin button is in output
  digitalWrite(eyePinL,0);
  digitalWrite(eyePinR,0);
  digitalWrite(eyePinL,255);
  digitalWrite(eyePinR,255);
  Serial.begin(9600);
  
} 

int leftServoPos(int val){
  return map(val, 0, 100, 52, 150);
}
int rightServoPos(int val){
  return map(val, 0, 100, 148, 50);
}
 
void loop() 
{ 
  analogReference(EXTERNAL);    //connect 3.3v to AREF
  accValue = analogRead(accX); // map(analogRead(accX), 0, 1023, 0, 255);   

  Serial.println(accValue);
  if ((accValue > 395) && (dir == 1)){ //451 - 320
      digitalWrite(eyePinL,0);
      digitalWrite(eyePinR,0);
      myservoL.attach(servoPinL);
      myservoR.attach(servoPinR); 
      for(pos = 0; pos <= 100; pos += 1) // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        // tell servo to go to position in variable 'pos' 
        myservoL.write( leftServoPos(pos) ); 
        myservoR.write( rightServoPos(pos) );              
        delay(8);                       
      }
      myservoL.detach();
      myservoR.detach();  
      dir *= -1;
      delay(500);
      return; 
    }
    
    
  if ((accValue < 340) && (dir == -1)){
      myservoL.attach(servoPinL);
      myservoR.attach(servoPinR);
      for(pos = 100; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        // tell servo to go to position in variable 'pos' 
        myservoL.write( leftServoPos(pos) ); 
        myservoR.write( rightServoPos(pos) );              
        delay(8);                        
      } 
      for(eyeFade = 0; eyeFade <= 255; eyeFade += 3) // fadein effect
      {                                  
        analogWrite(eyePinL,eyeFade);              
        analogWrite(eyePinR,eyeFade);              
        delay(25);                       
      } 
      myservoL.detach();
      myservoR.detach();
      dir *= -1;
      delay(500);
      return;
    }
   
  
} 

