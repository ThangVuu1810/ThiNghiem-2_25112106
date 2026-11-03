#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

volatile bool buttonPressed = false;

void IRAM_ATTR handleInterrupt() {
  buttonPressed = true; // ISR ngắn gọn, chỉ đặt cờ
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  ledcAttach(LED_PIN, 5000, 8); // Tần số 5000Hz, độ phân giải 8-bit
  
  // Gắn ngắt ngoài: khi tín hiệu chân BUTTON_PIN chuyển từ HIGH -> LOW (FALLING)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);
}

void loop() {
  static int brightness = 0, step = 1;
  
  if (buttonPressed) {
    buttonPressed = false;
    ledcWrite(LED_PIN, 0); delay(80);   // nháy tắt nhanh
    ledcWrite(LED_PIN, 255); delay(80); // nháy sáng nhanh
  }
  
  brightness += step;
  if (brightness <= 0 || brightness >= 255) step = -step;
  
  ledcWrite(LED_PIN, brightness);
  delay(10);
}
