/*
  ---------------------------------------------------------------
  Micro Mouse Robot - IR Version (3 Sensors)
  Sensors: 3x IR Reflectance (Left, Front, Right)
  Switch to select Left or Right Hand Rule
*/

// IR sensor pins
const int irLeft = A5;
const int irFront = A6;
const int irRight = A7;

void setup() {
  // motor setup reused
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(irLeft, INPUT);
  pinMode(irFront, INPUT);
  pinMode(irRight, INPUT);

  pinMode(ruleSwitch, INPUT_PULLUP);
}

int readIR(int pin) {
  return analogRead(pin);  // higher = more reflectance (wall)
}

void loop() {
  bool rightRule = digitalRead(ruleSwitch);
  int vL = readIR(irLeft);
  int vF = readIR(irFront);
  int vR = readIR(irRight);

  const int IR_THRESH = 400;  // adjust experimentally

  bool wallL = vL > IR_THRESH;
  bool wallF = vF > IR_THRESH;
  bool wallR = vR > IR_THRESH;

  if (rightRule) {
    if (!wallR) {
      // no wall on right -> turn right
      setMotors(150, -150);
    } else if (wallF) {
      // obstacle ahead -> turn left
      setMotors(-150, 150);
    } else {
      setMotors(200, 200);
    }
  } else {
    if (!wallL) {
      setMotors(-150, 150);
    } else if (wallF) {
      setMotors(150, -150);
    } else {
      setMotors(200, 200);
    }
  }
  delay(50);
}
