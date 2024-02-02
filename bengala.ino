#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int motorPin = 6;
const int buzzerPin = 8;
const int buzzerFrequency = 4000;

void setup() {
  Serial.begin(9600);

  if (!lox.begin(0x29)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }

  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(motorPin, LOW);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    int distance = measure.RangeMilliMeter;

    if (distance < 500 && distance > 400) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(motorPin, HIGH);
        tone(buzzerPin, buzzerFrequency);
        delay(100);
        digitalWrite(motorPin, LOW);
        noTone(buzzerPin);
        delay(300);
      }
    }

    if (distance < 400 && distance > 300) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(motorPin, HIGH);
        tone(buzzerPin, buzzerFrequency);
        delay(100);
        digitalWrite(motorPin, LOW);
        noTone(buzzerPin);
        delay(250);
      }
    }

    if (distance < 300 && distance > 200) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(motorPin, HIGH);
        tone(buzzerPin, buzzerFrequency);
        delay(100);
        digitalWrite(motorPin, LOW);
        noTone(buzzerPin);
        delay(200);
      }
    }

    if (distance < 200 && distance > 100) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(motorPin, HIGH);
        tone(buzzerPin, buzzerFrequency);
        delay(100);
        digitalWrite(motorPin, LOW);
        noTone(buzzerPin);
        delay(150);
      }
    }

    if (distance < 100) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(motorPin, HIGH);
        tone(buzzerPin, buzzerFrequency);
        delay(100);
        digitalWrite(motorPin, LOW);
        noTone(buzzerPin);
        delay(100);
      }
    }

    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(F(" mm"));
  } else {
    digitalWrite(motorPin, LOW);
    noTone(buzzerPin);
    Serial.println(F("Longe do Alcance"));
  }

  delay(10);
}

void ativaBuzzer(int numBipes) {
  for (int i = 0; i < numBipes; i++) {
    tone(buzzerPin, buzzerFrequency);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }
}

void desativaBuzzer() {
  noTone(buzzerPin);
}
