const int buttonPin = 7;
const int ledPin = 3;

int mode = 0;                // 0: 恆亮, 1: 慢閃, 2: 中閃, 3: 快閃
int lastButtonState = HIGH;
bool ledState = false;

unsigned long previousMillis = 0;   // 用於非阻塞閃爍
unsigned long interval = 0;         // 閃爍間隔時間
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // --- 按鈕去抖動 + 切換模式 ---
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastDebounceTime > debounceDelay) {
    mode = (mode + 1) % 4; // 四種模式循環
    lastDebounceTime = millis();
  }
  lastButtonState = buttonState;

  // --- 根據模式設定行為 ---
  switch (mode) {
    case 0: // 恆亮
      digitalWrite(ledPin, HIGH);
      break;

    case 1: // 慢閃
      interval = 1000; // 1秒
      blinkLED();
      break;

    case 2: // 中速閃
      interval = 500; // 0.5秒
      blinkLED();
      break;

    case 3: // 快閃
      interval = 200; // 0.2秒
      blinkLED();
      break;
  }
}

// --- 閃爍函式（非阻塞） ---
void blinkLED() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
  }
}
