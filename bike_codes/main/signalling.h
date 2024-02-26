#define red_pin A0
#define green_pin A1
#define buzzer 7
#define hallN A6
#define hallS A7


void signals_init(){
  pinMode(green_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(red_pin, LOW);
  digitalWrite(green_pin, LOW);
  noTone(buzzer);

}

void red(){
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);
}
void green(){
  digitalWrite(red_pin, LOW);
  digitalWrite(green_pin, HIGH);
}

void buzz(){
  tone(buzzer, 4000);
}

void checkNS(){
  int north=analogRead(hallN);
  int south=analogRead(hallS);
  if(north < 512){
    stopMotor();
    long start = millis();
    long now = millis();
    while(now - start< 3000){
      mpu.update();
      pid();
      red();
      if(now- start > 1000 && now - start < 2000)
      noTone(buzzer);
      else
      buzz();
      now = millis();

    }
    noTone(buzzer);
    digitalWrite(red_pin, LOW);
    start = millis();
    now = millis();
    while(now - start< 20000){
      mpu.update();
      pid();
      traversal();
      now = millis();

    }

  }
  else{
    noTone(buzzer);
    digitalWrite(red_pin, 0);
  }
    if(south < 512){
    stopMotor();
    long start = millis();
    long now = millis();
    while(now - start< 3000){
      mpu.update();
      pid();
      red();
      if(now- start > 1000 && now - start < 2000)
      noTone(buzzer);
      else
      buzz();
      now = millis();

    }
    noTone(buzzer);
    digitalWrite(green_pin, LOW);
    start = millis();
    now = millis();
    while(now - start< 20000){
      mpu.update();
      pid();
      traversal();
      now = millis();

    }
    

  }
  else{
    noTone(buzzer);
    digitalWrite(green_pin, 0);
  }

}