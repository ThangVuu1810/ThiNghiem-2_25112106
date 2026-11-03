#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  ledcAttach(LED_PIN, 5000, 8);
}

void loop() {
  for (int b = 0; b <= 255; b++) {
    ledcWrite(LED_PIN, b);
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("button pressed");
      delay(10); // each fade step takes 10 ms
    }
  }
  
  for (int b = 255; b >= 0; b--) {
    ledcWrite(LED_PIN, b);
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("button pressed");
      delay(10);
    }
  }
}
