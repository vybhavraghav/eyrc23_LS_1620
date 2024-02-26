#include "NRF.h"
#include "Wire.h"
#include "motor_controller.h"
// #include "BO_Motor.h" // already included in NRF
#include "DC_Motor.h"
#include "PID.h"

void setup() {
  // put your setup code here, to run once:
  dc_motor_init();
  Serial.begin(9600);
  Wire.begin();
  nrf_init();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  // to calibrate uncomment the following and check the offsets in serial Monitor

  // mpu.calcOffsets();
  // Serial.print("AccX:");Serial.print(mpu.getAccXoffset());
  // Serial.print("\tAccY:");Serial.print(mpu.getAccYoffset());
  // Serial.print("\tAccZ:");Serial.print(mpu.getAccZoffset());
  // Serial.print("\tGyX:");Serial.print(mpu.getGyroXoffset());
  // Serial.print("\tGyy:");Serial.print(mpu.getGyroYoffset());
  // Serial.print("\tGyZ:");Serial.println(mpu.getGyroZoffset());
  // delay(1000);

  // AccX:-0.02	AccY:-0.01	AccZ:0.07	GyX:-6.51	Gyy:0.84	GyZ:0.18

  mpu.setAccOffsets(-0.02, -0.01, 0.07);
  mpu.setGyroOffsets(-6.51,0.84, 0.18);

  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  Serial.println("Done!\n");

  // interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(2), encoderHandler,  CHANGE); 
  attachInterrupt(digitalPinToInterrupt(3), encoderHandler, CHANGE);
  



}

void loop() {
// put your main code here, to run repeatedly:
  // readRadioFB();
  mpu.update();
  pid();



}
