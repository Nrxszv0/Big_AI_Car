#include <Servo.h>
const int servo1 = 11;       // first servo
Servo myservo1;  // create servo object to control a servo
const int esc = 12;       // first servo
Servo myesc;  // create servo object to control a servo
const int buttonPin = 13;     // the number of the pushbutton pin
int buttonState = 0;
const int ledpin = 2;
char data = 0;
int driverState = 0;
int servoval = 100;

#define trigD1 9
#define echoD1 8
#define trigD2 7
#define echoD2 6
#define trigD3 5
#define echoD3 4
#define trigD4 3
#define echoD4 10

long duration, distance, distance1, distance2, distance3, distance4, difference, absDiff;

void setup() {
  // put your setup code here, to run once:

  myservo1.attach(servo1);  // attaches the servo
  myesc.attach(esc);  // attaches the servo
  pinMode(buttonPin, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(trigD1, OUTPUT);
  pinMode(echoD1, INPUT);
  pinMode(trigD2, OUTPUT);
  pinMode(echoD2, INPUT);
  pinMode(trigD3, OUTPUT);
  pinMode(echoD3, INPUT);
  pinMode(trigD4, OUTPUT);
  pinMode(echoD4, INPUT);

  myesc.write(80);
  myservo1.write(100);
  Serial.begin(9600);
}


void loop() {



  SonarSensor(trigD1, echoD1);
  distance1 = distance;
  SonarSensor(trigD2, echoD2);
  distance2 = distance;
  SonarSensor(trigD3, echoD3);
  distance3 = distance;
  SonarSensor(trigD4, echoD4);
  distance4 = distance;


  if (distance1 >= 300 || distance1 < 0) {
    distance1 = 0;
  }

  if (distance2 >= 300 || distance2 < 0) {
    distance2 = 0;
  }

  if (distance3 >= 300 || distance3 < 0) {
    distance3 = 0;
  }
  if (distance4 >= 300 || distance4 < 0) {
    distance4 = 0;
  }

  difference = (distance1 - distance2);
  absDiff = abs(difference);

  buttonState = digitalRead(buttonPin);

  if ((buttonState == HIGH) && (driverState == 0))
  {
    delay(1500);
    driverState = 1;
  }

  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data
    Serial.print(data);          //Print Value inside data in Serial monitor
    Serial.print("\n");

    if (data == '1')
    {
      driverState = 1;
    }
    if (data == '0')
    {
      driverState = 0;
    }
  }


  if (driverState == 0)
  {
    myesc.write(80);
    myservo1.write(100);
    digitalWrite(ledpin, LOW);
  }


  if (driverState == 1)
  {
    //Drive code here
    //variables: distance1, distance2, distance3 in cm
    digitalWrite(ledpin, HIGH);

    if (distance3 < 5 && distance3 != 0)
    {
      myesc.write(94);
      myservo1.write(65);
    }
    else
    {
      if ((distance4 < 10 && distance4 != 0) && (distance3 >= 20 || distance3 == 0))
      {
        myesc.write(92);
        myservo1.write(130);
      }
      else if ((distance4 < 10 && distance4 != 0) && (distance3 < 20 && distance3 != 0))
      {
        myesc.write(92);
        myservo1.write(65);
      }

      else
      {
        if ((distance1 == 0) || (distance1 > 45))
        {

          if ((distance3 <= 45) && (distance3 != 0))
          {
            myesc.write(91);
            myservo1.write(95);

            if ((distance2 <= 35) && (distance2 != 0))
            {
              myesc.write(92);
              myservo1.write(70);
            }
          }
          else
          {
            myesc.write(93);
            myservo1.write(130);
          }

        }
        else
        {
          myesc.write(91);
          myservo1.write(130);
        }


      }
    }


  }
  Serial.print(distance1);
  Serial.print("\n \n distance2 \n");
  Serial.print(distance2);
  Serial.print("\n \n distance3 \n");
  Serial.print(distance3);
  Serial.print("\n \n distance1 \n");
  //Serial.print(difference);
  //Serial.print("\n \n \n");

}





void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

}
