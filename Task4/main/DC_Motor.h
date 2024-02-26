/*
  this files contaains the functions related to the bike's dc motor
  (connected to omni wheel)
*/

#define in1 A2 // the dc motor input pin 1
#define in2 A3 // the dc motor input pin 2
#define enA 6 // the dc motor enable pin for controlling speed
#define off 50 // minimum pwm required to start the motor


void dc_motor_init(){
  /*
    inputs: None
    outputs: None
    this function is used to setup the DC motor in the void setup
    example:
      dc_motor_init()
*/
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
}

void motor_control(float pwm) {
  /*
    inputs: float pwm
    outputs: None
    this function is used to run the dc motor with the given speed(pwm value) 
    in the required direction
    example:
      motor_control(100);
*/
  if (pwm < 0) { // run the motor backward if speed is negative
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    pwm = -pwm;
  } else { // run the motor forward if the speed is positive
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  pwm = off + pwm; // add the minimum speed required for the motor to run

  // Serial.println(pwm);

  analogWrite(enA, pwm);
}