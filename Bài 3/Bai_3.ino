#include <Arduino.h>

const int potPin = 34;
const int ledPin = 26;
const int vccPin = 27;

float filtered = 0;
const float alpha = 0.15;

void setup() {
  Serial.begin(115200);

  pinMode(vccPin, OUTPUT);
  digitalWrite(vccPin, HIGH);

  analogReadResolution(12);
  ledcAttach(ledPin, 5000, 12);

  filtered = analogRead(potPin);
}

void loop() {
  int raw = analogRead(potPin);

  filtered = (alpha * raw) + ((1.0 - alpha) * filtered);
  int duty = (int)filtered;

  ledcWrite(ledPin, duty);

  Serial.print("Raw:");
  Serial.print(raw);
  Serial.print(",");
  Serial.print("Filtered:");
  Serial.println(duty);

  delay(20);
}
