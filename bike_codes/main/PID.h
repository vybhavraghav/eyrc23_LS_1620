/*
  this file contains the functons related to the PID control of the bike
*/
#include <MPU6050_light.h>

// following the PID contants of the roll and yaw pids
float Kr =  -86.3;
float Kr_d =-3.5; 
float Ky = 0.1;
float Ky_d =-2.34;
float Ky_i =0.001;
float iy = 0;
int setpoint = 0; // this is the yaw setpoint 


MPU6050 mpu(Wire);

void pid(){
    /*
    inputs: None
    outputs: None
    this function calculates the pid value to be sent to the motor to control the motor 
    and also sets the speed of the motor
    example:
      pid()
    */
  // reading the yaw value through the encoders setting the max yaw error to 35 so that the yaw control doesn't take charge 
  float y = constrain(setpoint + yawAngle , -35, 35);//constrain(setpoint + yawAngle, -35, 35);// yawAngle;//mpu.getAngleZ(); 
  float r_dot = mpu.getGyroX(); // read the r_dot value (angular velocity in roll) through teh gyroscope
  float y_dot = mpu.getGyroZ(); // read the y_dot value (angular velocity in yaw) through teh gyroscope
  float r = mpu.getAngleX() - Ky*y; //read the roll value and set the offset from it depending on the yaw
  iy += y; // yaw integral

  Serial.print("\Setpoint:");Serial.println(setpoint);
  // Serial.print("roll:");Serial.print(r);
  // Serial.print("\tyaw:");Serial.print(y);
  // Serial.print("\tr_dot:");Serial.print(r_dot);
  // Serial.print("\tyaw_dot:");Serial.println(y_dot);

  float output = Kr*r + Kr_d*r_dot - Ky_d*y_dot  + Ky_i*iy;//+ Ky*y // the output velocity required to control the bike

  motor_control(output);

}