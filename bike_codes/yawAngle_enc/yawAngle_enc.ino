long encoderValue = 0;
long lastEncoded= 0;
float yawAngle = 0;
int angle= 0;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(2), encoderHandler,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), encoderHandler, CHANGE);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(yawAngle);

}

void encoderHandler() {
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
  angle = encoderValue*360/715; 
  yawAngle = angle*0.1385;
  if (fabs(yawAngle) >= 360) encoderValue =0;

}