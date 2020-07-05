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
  square();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  esc.write(85);
  //  delay(dly);
  //  esc.write(70);
  //  ser.write(115);
  //  delay(2*dly);
}
void turnLeft() {
  ser.write(40);
  delay(250);
}
void turnStraight() {
  ser.write(90);
  delay(500);
}
void go() {
  esc.write(85);
  delay(dly);
  esc.write(70);
  delay(3 * dly);
}

void miniGo() {
  esc.write(85);
  delay(1000);
  esc.write(70);
  delay(3 * dly);
}
void square() {
  go();
  turnLeft();
  miniGo();
  turnStraight();
  go();

  turnLeft();
  miniGo();
  turnStraight();
  go();

  turnLeft();
  miniGo();
  turnStraight();
  go();

//  turnLeft();
//  miniGo();
//  turnStraight();
//  go();
}
