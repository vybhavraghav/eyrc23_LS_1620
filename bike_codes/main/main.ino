#include "Wire.h"
#include "motor_controller.h"
// #include "BO_Motor.h" // already included in NRF
#include "DC_Motor.h"
#include "PID.h"
#include "NRF.h"
#include "signalling.h"



void setup() {
  // put your setup code here, to run once:
  dc_motor_init();
  Serial.begin(9600);
  Wire.begin();
  signals_init();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  nrf_init();

   radio.startListening();

    while(Sw!=1){

    if (radio.available()) {
      radio.read(&received_data, sizeof(received_data));
      Serial.println("ok");
    }


    int x_value, y_value;
    sscanf(received_data, "%d,%d,%d", &x_value, &y_value,&Sw);

}


  radio.stopListening();

    Serial.println(F("Calculating offsets, do not move MPU6050"));
  // to calibrate uncomment the following and check the offsets in serial Monitor

  // mpu.calcOffsets();

  // mpu.calcOffsets();
  // Serial.print("AccX:");Serial.print(mpu.getAccXoffset());
  // Serial.print("\tAccY:");Serial.print(mpu.getAccYoffset());
  // Serial.print("\tAccZ:");Serial.print(mpu.getAccZoffset());
  // Serial.print("\tGyX:");Serial.print(mpu.getGyroXoffset());
  // Serial.print("\tGyy:");Serial.print(mpu.getGyroYoffset());
  // Serial.print("\tGyZ:");Serial.println(mpu.getGyroZoffset());
  // delay(1000);

  // AccX:-0.02	AccY:-0.01	AccZ:0.07	GyX:-6.51	Gyy:0.84	GyZ:0.18
  // AccX:-0.01	AccY:-0.03	AccZ:0.11	GyX:-7.13	Gyy:0.77	GyZ:0.23
  // AccX:0.01	AccY:0.01	AccZ:0.10	GyX:-6.92	Gyy:0.53	GyZ:0.05
  // AccX:-0.01	AccY:-0.06	AccZ:0.04	GyX:-5.93	Gyy:0.81	GyZ:0.28
  // AccX:-0.00	AccY:-0.01	AccZ:0.05	GyX:-6.26	Gyy:0.85	GyZ:0.29


  mpu.setAccOffsets(0.00, -0.01, 0.05);
  mpu.setGyroOffsets(-6.26,0.85, 0.29);

  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  Serial.println("Done!\n");

  // interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(2), encoderHandler,  CHANGE); 
  attachInterrupt(digitalPinToInterrupt(3), encoderHandler, CHANGE);
  long start = millis();
 
  while(millis() - start < 2000){
    mpu.update();
     pid();
    //  buzz();

  }
 start =millis();
  while(millis() - start < 1000){
    mpu.update();
     pid();
     buzz();

  }
  noTone(buzzer);
  



}

void loop() {
// put your main code here, to run repeatedly:
  mpu.update();
  pid();
  traversal();
  checkNS();



}
