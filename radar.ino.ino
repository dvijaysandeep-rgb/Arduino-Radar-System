#include <Servo.h>

Servo radarServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;
const int buzzerPin = 8;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  radarServo.attach(servoPin);
}

void loop() {

  // Left to Right
  for (int angle = 15; angle <= 165; angle++) {

    radarServo.write(angle);
    delay(30);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 20) {
      digitalWrite(buzzerPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
    }
  }

  // Right to Left
  for (int angle = 165; angle >= 15; angle--) {

    radarServo.write(angle);
    delay(30);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 20) {
      digitalWrite(buzzerPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
    }
  }
}

int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}