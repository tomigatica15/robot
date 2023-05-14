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
const int L1 = 6;
const int Lin = 7;
const int Lin2 = 8;
// Motor Right
const int R2 = 9;
const int Rin = 10;
const int Rin2 = 11;

// Ultrasonic
const int trigPin = 12;
const int echoPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(laserFront, INPUT);
  pinMode(laserLeft, INPUT);
  pinMode(laserRight, INPUT);
  pinMode(laserBack, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(Lin, OUTPUT);
  pinMode(Lin2, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(Rin, OUTPUT);
  pinMode(Rin2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void sleep() {
  delay(1000);
}

//          //
// Movement //
//          //

void moveRight() {
  digitalWrite(Lin, LOW);
  digitalWrite(Lin2, HIGH);
  analogWrite(L1, 100);
  digitalWrite(Rin, HIGH);
  digitalWrite(Rin2, LOW);
  analogWrite(R2, 200);
}

void verificationLeft() {
  valueLeft = digitalRead(laserLeft);
  if (valueLeft == HIGH) {
    //Serial.println("Blanco");
    moveRight();
  }
}

void moveLeft() {
  digitalWrite(Lin, HIGH);
  digitalWrite(Lin2, LOW);
  analogWrite(L1, 200);
  digitalWrite(Rin, LOW);
  digitalWrite(Rin2, HIGH);
  analogWrite(R2, 100);
}

void verificationRight() {
  valueRight = digitalRead(laserRight);
  if (valueRight == HIGH) {
    //Serial.println("Blanco");
    moveLeft();
  }
}

void moveBack() {
  digitalWrite(Lin, LOW);
  digitalWrite(Lin2, HIGH);
  analogWrite(L1, 200);
  digitalWrite(Rin, LOW);
  digitalWrite(Rin2, HIGH);
  analogWrite(R2, 200);
}

void verificationFront() {
  valueFront = digitalRead(laserFront);
  if (valueFront == HIGH) {
    //Serial.println("Blanco");
    moveBack();
  }
}

void moveFront() {
  digitalWrite(Lin, HIGH);
  digitalWrite(Lin2, LOW);
  analogWrite(L1, 200);
  digitalWrite(Rin, HIGH);
  digitalWrite(Rin2, LOW);
  analogWrite(R2, 200);
}

void verificationBack() {
  valueBack = digitalRead(laserBack);
  if (valueBack == HIGH) {
    //Serial.println("Blanco");
    moveFront();
  }
}

void moveEje() {
  digitalWrite(Lin, HIGH);
  digitalWrite(Lin2, LOW);
  analogWrite(L1, 255);
  digitalWrite(Rin, LOW);
  digitalWrite(Rin2, HIGH);
  analogWrite(R1, 255);
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
  while (valueBack == LOW && valueFront == LOW && valueRight == LOW && valueLeft == LOW) {
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