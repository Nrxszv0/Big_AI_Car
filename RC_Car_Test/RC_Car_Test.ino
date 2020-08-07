#include <Servo.h>
int serPin = 13, serVal = 115; //50, 115
int escPin = 12, escVal = 10; //95 150?.  //Around 70 = Stop. 80+ = Forwards(81 = slowest moving speed. 110+ = fastest speed). 65- = Backwards (anything below 55 is top reverse speed)
int startEscSpeed = 100;
int stopVal = 90;
int forwardSpeed = 107, reverseSpeed = 83;
int serPin1 = 4, serVal1;
int serPin2 = 5, serVal2;
int minAng = 0, maxAng = 140, minAng2 = 180, maxAng2 = 40, maxSerLeftAngle = 51, middleSerAngle = 90, maxSerRightAngle = 113;
int dly = 10, bDly = 250;
String angMsg = "Angle ", angMsg2 = ": ";
Servo ser;
Servo esc;
Servo ultraSer1;
Servo ultraSer2;

int echoPin1 = 4, trigPin1 = 5, echoPin2 = 3, trigPin2 = 2 ;
int ssDly = 2, sDly = 20;
float distanceIn;
float leftDistance, rightDistance, bucket, avgDistance;
float minDistance = 4, maxDistance = 40, reverseDistance = 4.5, turnDistance = 17;
int j, numMeas = 30;
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
  ser.write(90);
//  esc.write(startEscSpeed);
//  delay(10);
  esc.write(forwardSpeed);
}

void loop() {
  //  esc.write(forwardSpeed);
  //  delay(1500);
  //  esc.write(90);
  //  delay(9790709079);
  getDistances();
  driveCar();
  delay(100);
}
float distanceTest(int trigPin, int echoPin) {
  for (j = 0; j <= numMeas; j++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(ssDly);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(sDly);
    digitalWrite(trigPin, LOW);
    distanceIn = pulseIn(echoPin, HIGH) / 148.0;
    bucket += distanceIn;
  }
  avgDistance = bucket / numMeas;
  bucket = 0;
  return avgDistance;
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
  ser.write(middleSerAngle);
  Serial.println("Driving Forward");
}
void reverse() {
  esc.write(reverseSpeed);
  ser.write(middleSerAngle);
  Serial.println("Reversing");
}
void turnLeft() {
  serVal = map(rightDistance, minDistance, turnDistance, maxSerLeftAngle, middleSerAngle);
  Serial.print(rightDistance);
  //  Serial.print(leftDistance);
  Serial.print(",");
  Serial.print(minDistance);
  Serial.print(",");
  Serial.print(turnDistance);
  Serial.print(",");
  Serial.print(maxSerLeftAngle);
  Serial.print(",");
  Serial.print(middleSerAngle);
  Serial.print("     ");
  Serial.print("turningLeft");
  Serial.print("    ");
  Serial.println(serVal);
  ser.write(serVal);
}
void turnRight() {
  serVal = map(leftDistance, minDistance, turnDistance, maxSerRightAngle, middleSerAngle);
  Serial.print(leftDistance);
  //  Serial.print(rightDistance);
  Serial.print(",");
  Serial.print(minDistance);
  Serial.print(",");
  Serial.print(turnDistance);
  Serial.print(",");
  Serial.print(maxSerRightAngle);
  Serial.print(",");
  Serial.print(middleSerAngle);
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
