#include <Servo.h>
int serPin = 7, serVal = 115; //30, 115
int escPin = 6, escVal = 10; //95 150?
int startEscSpeed = 110;
int dly = 1000;
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
  esc.write(85);
  ser.write(40);
  delay(dly);
  esc.write(70);
  ser.write(115);
  delay(3*dly);
  
//esc.write(120);
//Serial.println("Car on");
//delay(3000);
//esc.write(0);
//Serial.println("Car off");
//delay(3000);
  
}
