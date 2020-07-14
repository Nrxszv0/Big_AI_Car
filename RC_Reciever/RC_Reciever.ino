const int CH1_PIN = 2;
const int CH2_PIN = 3;
const int CH3_PIN = 4;
int ch1, ch2, ch3, timeout = 25000, dly=10, deadzone = 20;
int serVal, switchVal, escVal;
int minVal = 990, maxVal = 1990, minCVal = 0, maxCVal = 180;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
ch1 = pulseIn(CH1_PIN, HIGH, timeout);
delay(dly);
ch2 = pulseIn(CH2_PIN, HIGH, timeout);
delay(dly);
ch3 = pulseIn(CH3_PIN, HIGH, timeout);
delay(dly);
serVal = map(pulseToPWM(ch1), -255, 255, minCVal, maxCVal);
escVal = map(pulseToPWM(ch2), -255, 255, minCVal, maxCVal);
switchVal = map(pulseToPWM(ch3), -255, 255, minCVal, maxCVal);
Serial.print(serVal);
Serial.print("   ");
Serial.print(escVal);
Serial.print("   ");
Serial.println(switchVal);
}
int pulseToPWM(int pulse) {
  if(pulse > minVal){
    pulse = map(pulse, minVal, maxVal, -500, 500);
    pulse = constrain(pulse, -255, 255);
  }
  else {
    pulse = 0;
  }
  if (abs(pulse) <= deadzone) {
    pulse = 0;
  }
  return pulse;
}
