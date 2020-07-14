#include <Servo.h>
int serPin = 7, serVal = 115; //30, 115
int escPin = 6, escVal = 10; //95 150?.  //Around 70 = Stop. 80+ = Forwards(81 = slowest moving speed. 110+ = fastest speed). 65- = Backwards (anything below 55 is top reverse speed)
int startEscSpeed = 110;
int serPin1 = 4, serVal1;
int serPin2 = 5, serVal2;
int minAng = 0, maxAng = 140, minAng2 = 180, maxAng2 = 40;
int dly = 15;
String angMsg = "Angle ", angMsg2 = ": ";
Servo ser;
Servo esc;
Servo ser1;
Servo ser2;

int echoPin = 9, trigPin = 8;
int ssDly = 2, sDly = 100;
float distanceIn;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ser.attach(serPin);
  esc.attach(escPin);
  ser1.attach(serPin1);
  ser2.attach(serPin2);
  ser1.write(140); // 0 = Forward 90 = Left 180 =Back
  ser2.write(40); // 180 = Forward 90 = Right 0 = Back
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  for ( int i = minAng; i <= maxAng; i++) {
    ser1.write(i);
    ser2.write(minAng2 - i);
    Serial.print(i);
    Serial.print("    ");
    Serial.println(minAng2 - i);
    delay(dly);
  }
  delay(500);
  for ( int i = maxAng; i >= 0; i--) {
    ser1.write(i);
    ser2.write(minAng2 - i);
    Serial.print(i);
    Serial.print("    ");
    Serial.println(minAng2 - i);
    delay(dly);
  }
  delay(500);



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
