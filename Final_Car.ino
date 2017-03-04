#include <Servo.h>

#define trigPinf 7
#define echoPinf 6
#define trigPinr 12
#define echoPinr 11
#define trigPinl 3
#define echoPinl 2

long duration, distance;

Servo left;
Servo right;

void setup() {
  left.attach(9);
  right.attach(10);
  Serial.begin(9600);
  pinMode(trigPinf, OUTPUT);
  pinMode(echoPinf, INPUT);
  pinMode(trigPinl, OUTPUT);
  pinMode(echoPinl, INPUT);
  pinMode(trigPinr, OUTPUT);
  pinMode(echoPinr, INPUT);
  delay(1000);
}

void loop() {
  if (SonarSensor(trigPinf, echoPinf)){
    if (SonarSensor(trigPinr, echoPinr)){
      if (SonarSensor(trigPinl, echoPinl)){
        forward();
        }
        else {rightTurn();}
      }
      else {leftTurn();}
    }
  else {
    if (SonarSensor(trigPinr, echoPinr)){
      rightTurn();      
      }
    else if (SonarSensor(trigPinl, echoPinl)){
      leftTurn();
      }
    else {
        while (!SonarSensor(trigPinr, echoPinr)){
         rightTurn(); 
         }
      }
   }
}

bool SonarSensor(int trigPin, int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance >= 20 or distance <= 0){
  Serial.println("true");
  return true;
  }
else{
  Serial.println("false");
  return false;
  }
}

void leftTurn() {
  left.write(0);
  right.write(0);
  delayMicroseconds(15);
}

void rightTurn() {
  left.write(180);
  right.write(180);
  delayMicroseconds(15);
}

void forward() {
  left.write(0);
  right.write(180);
  delayMicroseconds(15);
}

