#include <Servo.h>
int serPin = 7, serVal=115; //30, 115
Servo ser;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ser.attach(serPin);
}

void loop() {
  // put your main code here, to run repeatedly:
ser.write(serVal);

}
