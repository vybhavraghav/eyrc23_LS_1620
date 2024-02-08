#include "Wire.h"
#include <MPU6050_light.h>
#include "motor_controller.h"
#define in1 A2
#define in2 A3
#define enA 6
MPU6050 mpu(Wire);
unsigned long timer = 0;
float desiredAngle = 0.0;  
float off = 50;
float Kpr = 65; //50

float Kpy = 0;//7; //10
float Kir = 0; //1.5
float Kiy = 0;  //1
float kdr =3.5;
float Kdy = 0;
float prevError_yaw = 0.0; 
float prevError_roll = 0.0; 
float integral_roll = 0.0;   
float integral_yaw = 0.0;

void dc_motor_init(){
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
}

void motor_control(float pwm) {
  if (pwm < 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    pwm = -pwm;
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  pwm = off + pwm;

  Serial.println(pwm);

  analogWrite(enA, pwm);
}

void setup() {
  dc_motor_init();
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  mpu.calcOffsets();
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  Serial.println("Done!\n");

  attachInterrupt(digitalPinToInterrupt(2), encoderHandler,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), encoderHandler, CHANGE);
  
}

void loop() {
  mpu.update();
  
  // if((millis()-timer)>10){ // print data every 10ms

  // timer = millis();  
  float currentAngle_roll = (mpu.getAngleX());
  float currentAngle_yaw = (mpu.getAngleZ());
  // float currentAngle_yaw = yawAngle;
    if(currentAngle_yaw > 180) 
    currentAngle_yaw -=360;
    else if(currentAngle_yaw < -180)
      currentAngle_yaw +=360; 
  // if(currentAngle_yaw > 10 ){
  //   currentAngle_yaw = 10;
  // }
  // else if(currentAngle_yaw < -10 ){
  //   currentAngle_yaw = -10;
  // }
  // Serial.print(currentAngle_roll);Serial.print("\t");
  // Serial.print(currentAngle_yaw);Serial.print("\t");
  float error_roll = desiredAngle - currentAngle_roll;
  float error_yaw = desiredAngle - currentAngle_yaw;

  integral_roll += error_roll;
  integral_yaw += error_yaw;
  float derivative = error_yaw - prevError_yaw;
  float dr = error_roll - prevError_roll;
  float output;

  output =  ( Kpr * error_roll + Kir * integral_roll  - kdr*dr) - (Kpy * error_yaw + Kiy * integral_yaw - Kdy * derivative);

  motor_control(output);
  prevError_yaw = error_yaw;
  prevError_roll = error_roll;
  // timer = millis();
// }
}


