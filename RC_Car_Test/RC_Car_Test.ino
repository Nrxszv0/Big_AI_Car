#include <Servo.h>
int serPin = 7, serVal = 115; //30, 115
int escPin = 6, escVal = 10; //95 150?.  //Around 70 = Stop. 80+ = Forwards(81 = slowest moving speed. 110+ = fastest speed). 65- = Backwards (anything below 55 is top reverse speed)
int startEscSpeed = 110;
int serPin1 = 5, serVal1;
int dly = 1000;
Servo ser;
Servo esc;
Servo ser1;

int echoPin = 9, trigPin = 8;
int ssDly = 2, sDly = 20;
float distanceIn;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ser.attach(serPin);
  esc.attach(escPin);
  ser1.attach(serPin1);
  ser1.write(0);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(distanceTest());
  //   esc.write(110);
  //   delay(3500);
  //   esc.write(70);
  //   delay(100000);
  //  esc.write(85);
  //  ser.write(40);
  //  delay(dly);
  //  esc.write(70);
  //  ser.write(115);
  //  delay(3*dly);



  //esc.write(120);
  //Serial.println("Car on");
  //delay(3000);
  //esc.write(0);
  //Serial.println("Car off");
  //delay(3000);

}
float distanceTest() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(ssDly);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(sDly);
  digitalWrite(trigPin, LOW);
  distanceIn = pulseIn(echoPin, HIGH) / 148.0;
  return distanceIn;
}
