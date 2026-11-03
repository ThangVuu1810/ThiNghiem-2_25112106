#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2
#define DEBOUNCE_MS 500 // Ngưỡng chống dội (thay đổi giá trị này khi test)

volatile uint32_t debouncedCount = 0; // Số lần nhấn THỰC SỰ (đã chống dội)
volatile uint32_t rawEdgeCount = 0;   // Số sườn xuống THÔ (chưa chống dội)
volatile unsigned long lastInterruptTime = 0; // Mốc thời gian của sườn xuống hợp lệ gần nhất

// ISR: CÓ CHỐNG DỘI BẰNG millis()
void IRAM_ATTR handleInterrupt() {
  rawEdgeCount++; // Ghi nhận mọi sườn xuống thô để đối chiếu
  unsigned long now = millis();
  
  if (now - lastInterruptTime >= DEBOUNCE_MS) {
    // Đã qua thời gian chống dội -> đây là lần nhấn MỚI
    debouncedCount++;
    lastInterruptTime = now;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);
  Serial.println("San sang! Hay nhan nut nhieu lan.");
}

void loop() {
  // In ra kết quả liên tục để quan sát số lần đếm
  static uint32_t lastRaw = 0, lastDebounced = 0;
  
  // Chỉ in ra khi có sự thay đổi để Serial đỡ bị trôi
  if (rawEdgeCount != lastRaw || debouncedCount != lastDebounced) {
    Serial.print("Raw (Tho): ");
    Serial.print(rawEdgeCount);
    Serial.print(" | Debounced (Thuc te): ");
    Serial.println(debouncedCount);
    
    lastRaw = rawEdgeCount;
    lastDebounced = debouncedCount;
  }
}
