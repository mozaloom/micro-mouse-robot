/*
  Micro Mouse Robot - Ultrasonic Version (4 Sensors)
  Arduino Nano
  Motors: N20 12V 200 RPM DC Gear Motors
  Sensors: 4x HC-SR04 Ultrasonic
  Switch to select Left or Right Hand Rule
*/

// Motor driver pins
const int ENA = 5;   // PWM for left motor
const int IN1 = 2;
const int IN2 = 3;
const int ENB = 6;   // PWM for right motor
const int IN3 = 4;
const int IN4 = 7;

// Ultrasonic sensor pins
const int trigFL = 8; // front-left
const int echoFL = 9;
const int trigFR = 10; // front-right
const int echoFR = 11;
const int trigL = A0;  // left
const int echoL = A1;
const int trigR = A2;  // right
const int echoR = A3;

// Switch pin: LOW = Left-hand rule, HIGH = Right-hand rule
const int ruleSwitch = A4;

// Threshold distance (cm)
const int THRESH = 15;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigFL, OUTPUT);
  pinMode(echoFL, INPUT);
  pinMode(trigFR, OUTPUT);
  pinMode(echoFR, INPUT);
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);

  pinMode(ruleSwitch, INPUT_PULLUP);
  Serial.begin(9600);
}

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration > 0 ? (duration / 2) / 29 : 300;  // cm
}

void setMotors(int leftSpeed, int rightSpeed) {
  // left motor
  if (leftSpeed >= 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, leftSpeed);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, -leftSpeed);
  }
  // right motor
  if (rightSpeed >= 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, rightSpeed);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, -rightSpeed);
  }
}

void loop() {
  bool rightRule = digitalRead(ruleSwitch);  // HIGH = right-hand
  long dFL = readDistance(trigFL, echoFL);
  long dFR = readDistance(trigFR, echoFR);
  long dL = readDistance(trigL, echoL);
  long dR = readDistance(trigR, echoR);

  if (rightRule) {
    // Right-hand rule: keep right wall
    if (dR > THRESH) {
      // no wall on right -> turn right
      setMotors(150, -150);
    } else if (dFR < THRESH) {
      // obstacle ahead -> turn left
      setMotors(-150, 150);
    } else {
      // follow wall
      setMotors(200, 200);
    }
  } else {
    // Left-hand rule: keep left wall
    if (dL > THRESH) {
      // no wall on left -> turn left
      setMotors(-150, 150);
    } else if (dFL < THRESH) {
      // obstacle ahead -> turn right
      setMotors(150, -150);
    } else {
      // follow wall
      setMotors(200, 200);
    }
  }
  delay(50);
}