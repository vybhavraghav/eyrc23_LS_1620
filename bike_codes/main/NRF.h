/*
  this file contains the functions related to the nrf module for data transmission
*/

#include <SPI.h>
#include "BO_Motor.h"
#include <RF24.h>
int Sw = 0;


const byte add_1 = 5;
const byte add_2 = 10;

// int setpoint = 0; // this is the yaw setpoint 

char msg_1[50] = "";
char received_data[50]="";

RF24 radio(10, 8); // CE CSN pins 

void nrf_init(){
  /*
    inputs: None
    outputs: None
    this function is used to setup the nrf module in the void setup
    example:
      nrf_init()
*/
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


void traversal(){
    radio.startListening();

    delay(2);

    if (radio.available()) {
      radio.read(&received_data, sizeof(received_data));
      Serial.println("ok");
    }

    radio.stopListening();
    const char msg[] = "okay";
    radio.write(&msg, sizeof(msg));

    int x_value, y_value;
    sscanf(received_data, "%d,%d,%d", &x_value, &y_value, &Sw);

    // Serial.print("x_value\t");
    // Serial.println(x_value);
    // Serial.println(y_value);
    if (x_value>700){
      backward();
    }
    else if(x_value<300){
      forward();
    }
    else{
      stopMotor();
      
    }

    if (y_value>700){
      setpoint++;
    }
    else if(y_value<300){
      setpoint--;
    }

    if (Sw == 1){

        int start = millis();
        int now = millis();
        while(now - start< 5000){
          mpu.update();
          pid();
          tone(7, 4000);
          now = millis();

        }
    }

    

}

// void readRadioFB(){
//   /*
//     inputs: None
//     outputs: None
//     this function is used to read data from the controller about the front and back motions
//     example:
//       readRadioFB()
// */
//   radio.startListening();

//   delay(1);

//   if (radio.available()) {
//     radio.read(&msg_1, sizeof(msg_1));
//     // Serial.println(msg_1);
//   }


//   radio.stopListening();
//   const char msg_2[] = "okay";
//   radio.write(&msg_2, sizeof(msg_2));
//   int joy_value = atoi(msg_1);

//    if (joy_value > 600) {
//     forward();
//   } else if (joy_value < 300) {
//     backward();
//   } else {
//     stopMotor();
//   }

//   Serial.println(joy_value);
//   // Serial.println(msg_1);
//   delay(10);

// }

// void readRadioRL(){
//     /*
//     inputs: None
//     outputs: None
//     this function is used to read data from the controller to change the yaw point and steer the bike
//     example:
//       readRadioRL()
// */
//   radio.startListening();

//     delay(1);

//     if (radio.available()) {
//       radio.read(&msg_1, sizeof(msg_1));
//       // Serial.println(msg_1);
//     }


//     radio.stopListening();
//     const char msg_2[] = "okay";
//     radio.write(&msg_2, sizeof(msg_2));
//     int joy_value = atoi(msg_1);

//     if (joy_value > 600) {
//       setpoint ++;
//     } else if (joy_value < 300) {
//       setpoint--;
//     } else {
//       stopMotor();
//     }
//     delay(10);

// }