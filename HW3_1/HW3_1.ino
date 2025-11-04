// === 三顆 LED + 一顆按鈕 多模式控制 ===

// LED 腳位
const int led1 = 2;
const int led2 = 4;
const int led3 = 6;

// 按鈕腳位
const int buttonPin = 7;

// 計數器模式
int mode = 0;  // 初始模式為 0
bool buttonWasPressed = false;

// 流水燈控制
int seqIndex = 1;
int seqDirection = 1;
unsigned long lastUpdate = 0;

bool toggle = false;  // 閃爍模式開關
unsigned long lastFlash = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // 開機閃三次，確認 LED 功能正常
  for (int i = 0; i < 3; i++) {
    allOn();
    delay(150);
    allOff();
    delay(150);
  }
}

void loop() {
  int reading = digitalRead(buttonPin);

  // 按鈕下降緣偵測
  if (reading == LOW && !buttonWasPressed) {
    buttonWasPressed = true;
    mode++;
    if (mode > 4) mode = 1;  // 循環模式 1~4
  } else if (reading == HIGH) {
    buttonWasPressed = false;
  }

  // 根據模式控制 LED
  switch (mode) {
    case 1:  // 全亮
      allOn();
      break;

    case 2:  // 流水燈
      runSequence();
      break;

    case 3:  // 閃爍交替
      flashAlternate();
      break;

    case 4:  // 全關
      allOff();
      break;

    default:
      allOff();
      break;
  }
}

// ======= 函式區 =======
void allOn() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}

void allOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

// 模式 2：流水燈 (1→2→3→2→1)
void runSequence() {
  unsigned long current = millis();
  if (current - lastUpdate >= 150) {  // 每 150ms 更新一次
    lastUpdate = current;
    allOff();
    if (seqIndex == 1) digitalWrite(led1, HIGH);
    if (seqIndex == 2) digitalWrite(led2, HIGH);
    if (seqIndex == 3) digitalWrite(led3, HIGH);

    seqIndex += seqDirection;
    if (seqIndex == 3) seqDirection = -1;
    else if (seqIndex == 1) seqDirection = 1;
  }
}

// 模式 3：閃爍交替 (1、3 與 2)
void flashAlternate() {
  unsigned long current = millis();
  if (current - lastFlash >= 300) {  // 每 300ms 更新一次
    lastFlash = current;
    toggle = !toggle;

    if (toggle) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
    } else {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
    }
  }
}
