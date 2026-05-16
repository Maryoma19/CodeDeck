#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET = -1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

constexpr int MODE_BUTTON_PIN = 2;
constexpr int START_BUTTON_PIN = 3;
constexpr int RESET_BUTTON_PIN = 4;

constexpr int FOCUS_LED_PIN = 8;
constexpr int BREAK_LED_PIN = 9;
constexpr int DONE_LED_PIN = 10;

constexpr unsigned long FOCUS_DURATION_SECONDS = 25 * 60;
constexpr unsigned long BREAK_DURATION_SECONDS = 5 * 60;
constexpr unsigned long DEBOUNCE_MS = 180;

enum class Mode {
  Focus,
  Break
};

Mode currentMode = Mode::Focus;
bool timerRunning = false;
bool timerFinished = false;

unsigned long remainingSeconds = FOCUS_DURATION_SECONDS;
unsigned long lastTickMs = 0;
unsigned long lastModePressMs = 0;
unsigned long lastStartPressMs = 0;
unsigned long lastResetPressMs = 0;

bool buttonPressed(int pin, unsigned long &lastPressMs) {
  if (digitalRead(pin) == LOW && millis() - lastPressMs > DEBOUNCE_MS) {
    lastPressMs = millis();
    return true;
  }

  return false;
}

unsigned long durationForMode(Mode mode) {
  if (mode == Mode::Focus) {
    return FOCUS_DURATION_SECONDS;
  }

  return BREAK_DURATION_SECONDS;
}

const char *labelForMode(Mode mode) {
  if (mode == Mode::Focus) {
    return "FOCUS";
  }

  return "BREAK";
}

void resetTimer() {
  remainingSeconds = durationForMode(currentMode);
  timerRunning = false;
  timerFinished = false;
}

void switchMode() {
  currentMode = currentMode == Mode::Focus ? Mode::Break : Mode::Focus;
  resetTimer();
}

void updateTimer() {
  if (!timerRunning || timerFinished) {
    return;
  }

  unsigned long now = millis();
  if (now - lastTickMs < 1000) {
    return;
  }

  lastTickMs = now;

  if (remainingSeconds > 0) {
    remainingSeconds--;
  }

  if (remainingSeconds == 0) {
    timerRunning = false;
    timerFinished = true;
  }
}

void updateLeds() {
  digitalWrite(FOCUS_LED_PIN, currentMode == Mode::Focus && !timerFinished ? HIGH : LOW);
  digitalWrite(BREAK_LED_PIN, currentMode == Mode::Break && !timerFinished ? HIGH : LOW);
  digitalWrite(DONE_LED_PIN, timerFinished ? HIGH : LOW);
}

void drawDisplay() {
  unsigned int minutes = remainingSeconds / 60;
  unsigned int seconds = remainingSeconds % 60;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(labelForMode(currentMode));

  display.setTextSize(2);
  display.setCursor(0, 25);
  if (minutes < 10) {
    display.print('0');
  }
  display.print(minutes);
  display.print(':');
  if (seconds < 10) {
    display.print('0');
  }
  display.print(seconds);

  display.setTextSize(1);
  display.setCursor(0, 54);
  if (timerFinished) {
    display.print("Done. Press reset.");
  } else if (timerRunning) {
    display.print("Running");
  } else {
    display.print("Paused");
  }

  display.display();
}

void setup() {
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  pinMode(FOCUS_LED_PIN, OUTPUT);
  pinMode(BREAK_LED_PIN, OUTPUT);
  pinMode(DONE_LED_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  resetTimer();
  lastTickMs = millis();
}

void loop() {
  if (buttonPressed(MODE_BUTTON_PIN, lastModePressMs)) {
    switchMode();
  }

  if (buttonPressed(START_BUTTON_PIN, lastStartPressMs) && !timerFinished) {
    timerRunning = !timerRunning;
    lastTickMs = millis();
  }

  if (buttonPressed(RESET_BUTTON_PIN, lastResetPressMs)) {
    resetTimer();
  }

  updateTimer();
  updateLeds();
  drawDisplay();
}

