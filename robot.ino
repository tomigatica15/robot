// Optic
const int laserFront = 2;
const int laserRight = 3;
const int laserLeft = 4;
const int laserBack = 5;

int valueFront;
int valueRight;
int valueLeft;
int valueBack;

// Motor Left
const int ENA = 6;
const int IN1 = 7;
const int IN2 = 8;
// Motor Right
const int ENB = 9;
const int IN3 = 10;
const int IN4 = 11;

// Ultrasonic
const int trigPin = 12;
const int echoPin = 13;

void setup() {
  Serial.begin(9600);
  //Analog
  pinMode(laserFront, INPUT);
  pinMode(laserLeft, INPUT);
  pinMode(laserRight, INPUT);
  pinMode(laserBack, INPUT);
  //Motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void sleep() {
  delay(1000);
}

//           //
// Movements //
//           //

void moveRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 200);
}

void verificationLeft() {
  valueLeft = digitalRead(laserLeft);
  if (valueLeft == HIGH) {
    Serial.println("Blanco");
    moveRight();
  }
}

void moveLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);
}

void verificationRight() {
  valueRight = digitalRead(laserRight);
  if (valueRight == HIGH) {
    Serial.println("Blanco");
    moveLeft();
  }
}

void moveBack() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 200);
}

void verificationFront() {
  valueFront = digitalRead(laserFront);
  if (valueFront == HIGH) {
    Serial.println("Blanco");
    moveBack();
  }
}

void moveFront() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 200);
}

void verificationBack() {
  valueBack = digitalRead(laserBack);
  if (valueBack == HIGH) {
    Serial.println("Blanco");
    moveFront();
  }
}

void moveEje() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255);
}

//            //
// Ultrasonic //
//            //

void pulse() {
  long duration;
  int distance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance < 100) {
    moveFront();
  } else {
    moveEje();
  }
}

void attack() {
  while (valueBack == HIGH && valueFront == HIGH && valueRight == HIGH && valueLeft == HIGH) {
    pulse();
    delay(50);
  }
}

void loop() {
  attack();
  verificationLeft();
  sleep();
  verificationRight();
  sleep();
  verificationBack();
  sleep();
  verificationFront();
  sleep();
}