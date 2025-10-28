#define BUTTON_PIN 2
#define RED_PIN    9
#define GREEN_PIN  10
#define BLUE_PIN   11

unsigned long buttonPressedTime = 0; 
unsigned long lastPressTime = 0;     
unsigned long lastColorChange = 0;    
int colorIndex = 0;
bool isHappy = false;
bool isLongPress = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    if (buttonPressedTime == 0) {
      buttonPressedTime = currentTime; 
    }
    if (currentTime - buttonPressedTime >= 3000) {
      isLongPress = true;
    }
  } else {
    if (buttonPressedTime != 0) {
      if (!isLongPress) {
        isHappy = true;
        lastColorChange = currentTime;
      }
      lastPressTime = currentTime;  
    }
    buttonPressedTime = 0;  
    isLongPress = false;
  }

  if (currentTime - lastPressTime > 5000) {
    isHappy = false;
  }

  if (buttonState == LOW && isLongPress) {
    setColor(0, 128, 64);  
  } else if (isHappy) {
    happyMode(currentTime);
  } else {
    sadMode(currentTime);
  }
}
void happyMode(unsigned long currentTime) {
  if (currentTime - lastColorChange > 200) {
    lastColorChange = currentTime;
    colorIndex = (colorIndex + 1) % 3;
  }

  switch (colorIndex) {
    case 0: setColor(0, 100, 255); break;     
    case 1: setColor(0, 180, 180); break;     
    case 2: setColor(120, 80, 200); break;    
  }
}
void sadMode(unsigned long currentTime) {
  float period = 4000.0;  
  float phase = (currentTime % (unsigned long)period) / period * 2 * PI;
  int brightness = (sin(phase) + 1) * 127.5;
  setColor(brightness, 0, 0);
}

void setColor(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}
