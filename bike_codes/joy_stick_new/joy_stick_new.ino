#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);


const byte add_1 = 5;
const byte add_2 = 10;
const int VRx = A2; // analog pin for x-axis
const int VRy = A1; // analog pin for y-axis
const int SW = A0;  // Digital pin for the button

char msg_2[50] = "";
char joystick_data[20];

void setup() {
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);

  int result = radio.begin();

  if (result) {
    Serial.println("NRF module Working");
  } else {
    Serial.println("NRF module ERROR ");
  }

  radio.openWritingPipe(add_1);
  radio.openReadingPipe(1, add_2);
  // Set data rate to RF24_250KBPS, RF24_1MBPS, or RF24_2MBPS
  radio.setDataRate(RF24_2MBPS); // Adjust the data rate as needed

  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  int x_value = analogRead(VRx);
  int y_value = analogRead(VRy);
  int button_state = !digitalRead(SW);

  // Format the data as a string and concatenate x and y values
  sprintf(joystick_data, "%d,%d,%d", x_value, y_value, button_state);

  radio.stopListening();
  radio.write(&joystick_data, sizeof(joystick_data));
  // Serial.print
  delay(4); // Introduce a small delay after write

  radio.startListening();
  if (radio.available()) {
    radio.read(&msg_2, sizeof(msg_2));
    Serial.println(msg_2);
    // Serial.println(joystick_data);

    // if (x_value > 1 || y_value > 1) {
    //   Serial.println(joystick_data);
    // } else {
    //   Serial.println(msg_2);
    // }
  }
  delay(4); // Give some time for the module to switch to listening mode
}
