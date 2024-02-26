/*
  this file contains all the functions related to the BO motor control
*/
#include <SPI.h>
// #include <RF24.h>
#define enB 5 // enable pin of bo motor to control speed
#define in3 9// input pin 1 of bo motor
#define in4 4// input pin 2 of bo motor
// RF24 radio(10, 8);




void bo_motor_init(){
/*
    inputs: None
    outputs: None
    this function is used to setup the BO motor in the void setup
    example:
      bo_motor_init()
*/

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void forward(){
/*
    inputs: None
    outputs: None
    this function is used to run the bo motor forward
    example:
      forward()
*/

  analogWrite(enB, 175);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
}


void backward(){
  /*
    inputs: None
    outputs: None
    this function is used to run the bo motor backward
    example:
      backward()
*/
  analogWrite(enB, 205);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

void stopMotor() {
  /*
    inputs: None
    outputs: None
    this function is used to stop the bo motor
    example:
      stopMotor()
*/
  analogWrite(enB, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


