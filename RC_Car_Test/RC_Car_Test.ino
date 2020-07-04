#include <Servo.h>
int serPin = 7, serVal=115; //30, 115
int escPin = 6, escVal=10; //95 150?
int startEscSpeed = 110;
Servo ser;
Servo esc;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ser.attach(serPin);
esc.attach(escPin);
//esc.write(startEscSpeed);
//delay(30);
}

void loop() {
  // put your main code here, to run repeatedly:
//ser.write(serVal);
//esc.write(90);
ser.write(115);
//delay(500);
//ser.write(100);
//delay(500);
//esc.write(0);
//esc.write(0);
//delay(10000);
//delay(10000000);

}
