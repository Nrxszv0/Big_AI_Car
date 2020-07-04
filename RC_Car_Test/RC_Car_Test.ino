#include <Servo.h>
int serPin = 7, serVal = 115; //30, 115
int escPin = 6, escVal = 10; //95 150?
int startEscSpeed = 110;
Servo ser;
Servo esc;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ser.attach(serPin);
  esc.attach(escPin);

}

void loop() {
  // put your main code here, to run repeatedly:
  //  ser.write(115);
  //  delay(1000);
  //  ser.write(50);
  //  delay(1000);
  esc.write(100);
  delay(1000);
  esc.write(0);
  delay(1000);
  ser.write(70);
  delay(1000);
  ser.write(100);
  delay(1000);
  esc.write(80);
  delay(1000);
}
