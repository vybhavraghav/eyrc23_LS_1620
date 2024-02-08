#include "Wire.h"
#include <MPU6050_light.h>
#define in1 A2
#define in2 A3
#define enA 6
MPU6050 mpu(Wire);
unsigned long timer = 0;
float desiredAngle = 0.0;  
float off = 50;
float Kpr = 70; //50

float Kpy = 5;//7; //10
float Kir = 0; //1.5
float Kiy = 0;  //1
float kdr = 2.5;
float Kdy = 0;
float pr = 30;
float py = 180;
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
    // if(currentAngle_yaw > 10 ){
  //   currentAngle_yaw = 10;
  // }
  // else if(currentAngle_yaw < -10 ){
  //   currentAngle_yaw = -10;
  // }
  //   float currentAngle_roll = mpu.getAngleX();
  // float currentAngle_yaw = mpu.getAngleZ();
  float error_roll = desiredAngle - currentAngle_roll;
  float error_yaw = desiredAngle - currentAngle_yaw;

  integral_roll += error_roll;
  integral_yaw += error_yaw;
  float derivative = error_yaw - prevError_yaw;
  float dr = error_roll - prevError_roll;
  float output;

  // if (currentAngle_roll < 2 && currentAngle_roll > -2){
  output =  (abs(error_roll)/pr)*( Kpr * error_roll + + Kir * integral_roll  - kdr*dr) + (abs(error_yaw)/py)*(Kpy * error_yaw + Kiy * integral_yaw - Kdy * derivative);
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