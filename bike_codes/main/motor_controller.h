/*
  this file contains function that read the encoders data
*/
long encoderValue = 0; // present encoder count
long lastEncoded= 0; // previous encoder count
float yawAngle = 0; // yaw angle calculated
int angle= 0; // angle the wheel has rotated

void encoderHandler() {
    /*
    inputs: None
    outputs: None
    this function is used to read the encoder values and calculate the yaw angle
    example:
      encoderHandler()
    */
  int MSB = digitalRead(2); //MSB = most significant bit
  int LSB = digitalRead(3); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue++; //CW
  }
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue--; //CCW
  }

  lastEncoded = encoded; //store this value for next time 
  angle = encoderValue*360/715; // relation between encoder count and wheel angle
  yawAngle = angle*0.1385; // relation between wheel angle and yaw angle
  if (fabs(yawAngle) >= 360) encoderValue =0; // reset the yaw angle when it reaches 360

}