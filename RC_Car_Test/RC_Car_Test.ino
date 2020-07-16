#include <Servo.h>
int serPin = 7, serVal = 115; //30, 115
int escPin = 6, escVal = 10; //95 150?.  //Around 70 = Stop. 80+ = Forwards(81 = slowest moving speed. 110+ = fastest speed). 65- = Backwards (anything below 55 is top reverse speed)
int startEscSpeed = 110;
int stopVal = 90;
int forwardSpeed = 112, reverseSpeed = 55;
int serPin1 = 4, serVal1;
int serPin2 = 5, serVal2;
int minAng = 0, maxAng = 140, minAng2 = 180, maxAng2 = 40, maxLeftAngle = 0, middleAngle = 90, maxRightAngle = 180;
int dly = 10, bDly = 250;
String angMsg = "Angle ", angMsg2 = ": ";
Servo ser;
Servo esc;
Servo ultraSer1;
Servo ultraSer2;

int echoPin1 = 9, trigPin1 = 8, echoPin2 = 11, trigPin2 = 10 ;
int ssDly = 2, sDly = 20;
float distanceIn;
float leftDistance, rightDistance;
float minDistance = 0, maxDistance = 40, reverseDistance = 4.5, turnDistance = 15;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ser.attach(serPin);
  esc.attach(escPin);
  ultraSer1.attach(serPin1);
  ultraSer2.attach(serPin2);
  ultraSer1.write(85); // 0 = Forward 90 = Left 180 =Back // 85
  ultraSer2.write(105); // 180 = Forward 90 = Right 0 = Back // 105
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  ser.write(middleAngle);
}

void loop() {
//  esc.write(reverseSpeed);
//  delay(1000);
//  esc.write(90);
//  delay(9790709079);
  getDistances();
  driveCar();
  delay(100);

}
float distanceTest(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(ssDly);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(sDly);
  digitalWrite(trigPin, LOW);
  distanceIn = pulseIn(echoPin, HIGH) / 148.0;
  return distanceIn;
}
void moveServos() {
  for ( int i = minAng; i <= maxAng; i++) {
    ultraSer1.write(i);
    ultraSer2.write(minAng2 - i);
    getDistances();
    delay(dly);
  }
  delay(bDly);
  for ( int i = maxAng; i >= 0; i--) {
    ultraSer1.write(i);
    ultraSer2.write(minAng2 - i);
    getDistances();
    delay(dly);
  }
  delay(bDly);
}
void getDistances() {
  leftDistance = distanceTest(trigPin1, echoPin1);
  leftDistance = constrain(leftDistance, minDistance, maxDistance);
  rightDistance = distanceTest(trigPin2, echoPin2);
  rightDistance = constrain(rightDistance, minDistance, maxDistance);
  Serial.print(leftDistance);
  Serial.print("    ");
  Serial.print(rightDistance);
  Serial.print("\t\t");
}
void stop() {
  esc.write(stopVal);
}
void forward() {
  esc.write(forwardSpeed);
  ser.write(middleAngle);
  Serial.println("Driving Forward");
}
void reverse() {
  esc.write(65);
  ser.write(middleAngle);
  Serial.println("Reversing");
}
void turnLeft() {
  serVal = map(rightDistance, minDistance, turnDistance, maxLeftAngle, middleAngle);
  Serial.print(rightDistance);
  //  Serial.print(leftDistance);
  Serial.print(",");
  Serial.print(minDistance);
  Serial.print(",");
  Serial.print(turnDistance);
  Serial.print(",");
  Serial.print(maxLeftAngle);
  Serial.print(",");
  Serial.print(middleAngle);
  Serial.print("     ");
  Serial.print("turningLeft");
  Serial.print("    ");
  Serial.println(serVal);
  ser.write(serVal);
}
void turnRight() {
  serVal = map(leftDistance, minDistance, turnDistance, maxRightAngle, middleAngle);
  Serial.print(leftDistance);
  //  Serial.print(rightDistance);
  Serial.print(",");
  Serial.print(minDistance);
  Serial.print(",");
  Serial.print(turnDistance);
  Serial.print(",");
  Serial.print(maxRightAngle);
  Serial.print(",");
  Serial.print(middleAngle);
  Serial.print("     ");
  Serial.print("turningRight");
  Serial.print("    ");
  Serial.println(serVal);
  ser.write(serVal);
}
void driveCar() {
  if (leftDistance < turnDistance || rightDistance < turnDistance) {
    if ((leftDistance <= reverseDistance) && (rightDistance <= reverseDistance)) {
      reverse();
    }
    else if (leftDistance < rightDistance) {
      turnRight();
    }
    else if (rightDistance < leftDistance) {
      turnLeft();
    }
    else {
      forward();
    }
  }
  else {
    forward();
  }
}
