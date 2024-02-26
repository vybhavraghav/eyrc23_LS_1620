#include "Wire.h"
#include <MPU6050_light.h>
#define in1 A2
#define in2 A3
#define enA 6
MPU6050 mpu(Wire);
unsigned long timer = 0;
float desiredAngle = 0.0;  
float off = 50;
float Kpr = 80; //50

float Kpy = 0;//7; //10
float Kir = 0; //1.5
float Kiy = 0;  //1
float kdr = 3.5;
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
  
}

void loop() {
  mpu.update();
  
  // if((millis()-timer)>10){ // print data every 10ms

  // timer = millis();  
  float currentAngle_roll = (mpu.getAngleX());
  float currentAngle_yaw = (mpu.getAngleZ());
    if(currentAngle_yaw > 180) 
    currentAngle_yaw -=360;
    else if(currentAngle_yaw < -180)
      currentAngle_yaw +=360; 
    if(currentAngle_yaw > 20 ){
    currentAngle_yaw = 20;
  }
  else if(currentAngle_yaw < -20 ){
    currentAngle_yaw = -20;
  }
  //   float currentAngle_roll = mpu.getAngleX();
  // float currentAngle_yaw = mpu.getAngleZ();

  float error_yaw = 0 - currentAngle_yaw;
  float derivative = error_yaw - prevError_yaw;
  integral_yaw += error_yaw;
  desiredAngle = -Kpy * error_yaw + Kdy*derivative - Kiy*integral_yaw;
  float error_roll = desiredAngle - currentAngle_roll;

  integral_roll += error_roll;
  float dr = error_roll - prevError_roll;
  float output;

  // if (currentAngle_roll < 2 && currentAngle_roll > -2){
  output =  ( Kpr * error_roll + + Kir * integral_roll  - kdr*dr); //+ Kpy * error_yaw + Kiy * integral_yaw - Kdy * derivative;
  // Serial.println(currentAngle_yaw);
  // // output = yaw_corr;
  // // Serial.println(output);
  // }
  // else{
  //   output = Kpr * error_roll + + Kir * integral_roll  - kdr*dr;
    
  //   Serial.println(output);
  // }
  // // Serial.println(output);
  motor_control(output);
  prevError_yaw = error_yaw;
  prevError_roll = error_roll;
  // timer = millis();
// }
}