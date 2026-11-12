#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd(0);
Servo doorLock;

const int servoPin = 10;
const int buzzerPin = 11;

const String masterPassword = "1234";
String enteredPassword = "";

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600); // 1. Turns on the Serial Monitor
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  
  doorLock.attach(servoPin);
  doorLock.write(0);
  
  pinMode(buzzerPin, OUTPUT);
  resetScreen();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    digitalWrite(buzzerPin, HIGH);
    delay(25);
    digitalWrite(buzzerPin, LOW);

    if (key == '*') {
      enteredPassword = "";
      resetScreen();
    } 
    else if (key == '#') {
      checkPassword();
    } 
    else {
      if (enteredPassword.length() < 4) {
        enteredPassword += key;
        lcd.setCursor(enteredPassword.length() - 1, 1);
        lcd.print("*");
      }
    }
  }
}

// 3. Musical note generator for the buzzer
void playNote(int pitchDelay, int durationMs) {
  long cycles = (long)durationMs * 1000 / (pitchDelay * 2);
  for (long i = 0; i < cycles; i++) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(pitchDelay);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(pitchDelay);
  }
}

void checkPassword() {
  lcd.clear();
  if (enteredPassword == masterPassword) {
    // 2. Two-line talking text on LCD
    lcd.setCursor(0, 0);
    lcd.print("Welcome Home!");
    lcd.setCursor(0, 1);
    lcd.print("Door Unlocked");
    
    // 1. Voice sentence in Serial Monitor
    Serial.println("VOICE: Welcome home! The door is now unlocked.");

    // 3. Cheerful rising melody
    playNote(1915, 120);
    delay(30);
    playNote(1519, 120);
    delay(30);
    playNote(1275, 250);

    doorLock.write(90);
    delay(4000);
    doorLock.write(0);
    Serial.println("VOICE: Door is locked again.");
  } else {
    // 2. Two-line warning text on LCD
    lcd.setCursor(0, 0);
    lcd.print("Wrong Password!");
    lcd.setCursor(0, 1);
    lcd.print("Try Again...");
    
    // 1. Voice warning in Serial Monitor
    Serial.println("VOICE: Warning! Incorrect password. Please try again.");

    // 3. Sad descending alarm
    playNote(2500, 250);
    delay(50);
    playNote(3400, 450);
    delay(1500);
  }
  enteredPassword = "";
  resetScreen();
}

void resetScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}
