#include <SPI.h>
#include <RF24.h>
#define enB 5
#define in3 9
#define in4 4
RF24 radio(10, 8);

const byte add_1 = 5;
const byte add_2 = 10;

char msg_1[50] = "";

void bo_motor_init(){
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void forward(){
  analogWrite(enB, 100);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
}

void backward(){
  analogWrite(enB, 100);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

void stopMotor() {
  analogWrite(enB, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  
  bo_motor_init();
  Serial.begin(9600);

  int result = radio.begin();

  if (result) {
    Serial.println("NRF module Working");
  } 
  else {
     Serial.println("NRF module ERROR ");
  }

  radio.openWritingPipe(add_2);
  radio.openReadingPipe(1, add_1);
// Set data rate to RF24_250KBPS, RF24_1MBPS, or RF24_2MBPS
  radio.setDataRate(RF24_2MBPS); // Adjust the data rate as needed
  radio.setPALevel(RF24_PA_MIN);

}

void loop() {
  radio.startListening();

  delay(10);

  if (radio.available()) {
    radio.read(&msg_1, sizeof(msg_1));
    // Serial.println(msg_1);
  }


  radio.stopListening();
  const char msg_2[] = "okay";
  radio.write(&msg_2, sizeof(msg_2));
  int joy_value = atoi(msg_1);

   if (joy_value > 600) {
    forward();
  } else if (joy_value < 300) {
    backward();
  } else {
    stopMotor();
  }

  Serial.println(joy_value);
  Serial.println(msg_1);

  delay(10);
}