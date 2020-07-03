#include <Servo.h>

int servoPinLow = 8;
int servoPinHigh = 9;

Servo ServoLow;
Servo ServoHigh;

void setup() {
  ServoLow.attach(servoPinLow);
  ServoHigh.attach(servoPinHigh);
}

void loop() {
    ServoHigh.write(0);
    ServoLow.write(0);
    delay(1000);
    ServoHigh.write(45);
    ServoLow.write(90);
    delay(1000);
    ServoHigh.write(90);
    ServoLow.write(180);
    delay(1000);
}