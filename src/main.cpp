#include <Arduino.h>
int LED1 = A0;
int LED2 = A1;
int LED3 = A2;
int LED4 = A3;
int loadingStage = 0;
unsigned long startTime = 0;
int debounce = 100;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32-S3!");
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void loop() {
  bool switchState1 = digitalRead(10);
  bool switchState2 = digitalRead(9);
  bool switchState3 = digitalRead(6);
  bool switchState4 = digitalRead(5);

  if (loadingStage == 0) {
    delay(debounce);
    if (switchState1) {
      delay(debounce);
      Serial.println("Loading New Energy Storage Device");
      startTime = millis();
      loadingStage = 1;
    }
    else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    }
  }
  else if (loadingStage == 1) {
    digitalWrite(LED1, HIGH);
    if (switchState1) {
      delay(debounce);
      Serial.println("Loading Process Canceled");
      loadingStage = 0;
      delay(debounce);
    }
    else if (millis() - startTime >= 3000) {
      delay(debounce);
      Serial.println("Device Loaded");
      loadingStage = 2;
    }
  }
  else if (loadingStage == 2) {
    digitalWrite(LED2, HIGH);
    if (switchState2) {
      delay(debounce);
      Serial.println("Material inserted");

    }
    if (switchState3) {

      Serial.println("Starting detonation countdown");
      loadingStage = 3;
      startTime = millis();
    }
  }
  else if (loadingStage == 3) {
    if (millis() - startTime >= 5000) {
      digitalWrite(LED3, HIGH);
      Serial.println("Detonation complete...Device ready");
      loadingStage = 4;
    }
    else {
      digitalWrite(LED3, HIGH);
      delay(250);
      digitalWrite(LED3, LOW);
      delay(250);
    }
  }
  else if (loadingStage == 4) {
    digitalWrite(LED4, HIGH);
    if (switchState4) {
      Serial.println("Device placed into vehicle");
      loadingStage = 0;
    }
  }
}