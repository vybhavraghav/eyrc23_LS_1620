#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte add_1 = 5;
const byte add_2 = 10;
const int VRx = A2; // analog pin for x-axis 
const int VRy = A1; // analog pin for y-axis
const int SW  = A0;  // Digital pin for the button

char msg_2[50] = "";
char x_new[10];
int x_value, y_value, button_state;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);

  int result = radio.begin();

  if (result) {
    Serial.println("NRF module Working");
  } 
  else {
     Serial.println("NRF module ERROR ");
  }

  radio.openWritingPipe(add_1);
  radio.openReadingPipe(1, add_2);
  // Set data rate to RF24_250KBPS, RF24_1MBPS, or RF24_2MBPS
  radio.setDataRate(RF24_2MBPS); // Adjust the data rate as needed

  radio.setPALevel(RF24_PA_MIN);
  
}

void loop() {
  //const char msg_1[] = "joy stick output";
  int x_value = analogRead(VRx);
  int y_value = analogRead(VRy);
  int button_state = !digitalRead(SW);

 sprintf(x_new, "%d", x_value);

  radio.stopListening();
  radio.write(&x_new, sizeof(x_new));
  delay(10); // Introduce a small delay after write

  radio.startListening();
  delay(10); // Give some time for the module to switch to listening mode
  if (radio.available()) {
    radio.read(&msg_2, sizeof(msg_2));
    if(x_value>1){
      Serial.println(x_new); 
    }
    else{
      Serial.println(msg_2);
    }
  }
}