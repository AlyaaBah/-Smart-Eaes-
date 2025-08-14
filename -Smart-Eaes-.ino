#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(A0, A1);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

const int IR_IN = 10;
const int IR_OUT = 11;
const int servoPin = 12;

int totalSlots = 3;
int availableSlots = 3;

unsigned long lastTriggerTime = 0;
const unsigned long debounceDelay = 2000;

int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

int upButton = 8;
int downButton = 9;

int trigPin = 6;
int echoPin = 7;

bool upPressed = false;
bool downPressed = false;

int closeCounter = 0;

#define LED1 A2
#define LED2 A3
#define LED3 13

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(IR_IN, INPUT);
  pinMode(IR_OUT, INPUT);

  myservo.attach(servoPin);
  myservo.write(100);

  lcd.setCursor(0, 0);
  lcd.print("   ARDUINO PARK  ");
  lcd.setCursor(0, 1);
  lcd.print("   WELCOME! :)   ");
  delay(2000);
  lcd.clear();
  displaySlots();

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  int inState = digitalRead(IR_IN);
  int outState = digitalRead(IR_OUT);
  unsigned long currentTime = millis();

  if (inState == LOW && currentTime - lastTriggerTime > debounceDelay) {
    if (availableSlots > 0) {
      availableSlots--;
      openGate("CAR ENTERED");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   SORRY :(     ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full ");
      delay(2000);
    }
    lastTriggerTime = currentTime;
    displaySlots();
  }

  if (outState == LOW && currentTime - lastTriggerTime > debounceDelay) {
    if (availableSlots < totalSlots) {
      availableSlots++;
      openGate("CAR EXITED");
    }
    lastTriggerTime = currentTime;
    displaySlots();
  }

  if (digitalRead(upButton) == LOW && !upPressed) {
    upPressed = true;
    moveUp();
  }
  if (digitalRead(downButton) == LOW && !downPressed) {
    downPressed = true;
    moveDown();
  }
  if (digitalRead(upButton) == HIGH) upPressed = false;
  if (digitalRead(downButton) == HIGH) downPressed = false;

  long duration, distance;
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 20) closeCounter++;
  else closeCounter = 0;

  if (closeCounter >= 2) {
    openDoor();
    closeCounter = 0;
  }

  if (bluetooth.available()) {
    String command = bluetooth.readStringUntil('\n');
    command.trim();

    if (command == "open") {
      openGate("Remote Open");
    } else if (command == "up") {
      moveUp();
    } else if (command == "down") {
      moveDown();
    } else if (command == "door") {
      openDoor();
    } else if (command == "1on") digitalWrite(LED1, HIGH);
    else if (command == "1off") digitalWrite(LED1, LOW);
    else if (command == "2on") digitalWrite(LED2, HIGH);
    else if (command == "2off") digitalWrite(LED2, LOW);
    else if (command == "3on") digitalWrite(LED3, HIGH);
    else if (command == "3off") digitalWrite(LED3, LOW);
    else if (command == "allon") {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
    }
    else if (command == "alloff") {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
  }

  delay(300);
}

void openGate(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  lcd.setCursor(0, 1);
  lcd.print("  Opening Gate  ");
  myservo.write(0);
  delay(4000);
  myservo.write(100);
}

void displaySlots() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME :)");
  lcd.setCursor(0, 1);
  lcd.print("Left: ");
  lcd.print(availableSlots);
  lcd.print("/");
  lcd.print(totalSlots);
}

void moveUp() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  delay(1000);
  stopElevator();
}

void moveDown() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  delay(1000);
  stopElevator();
}

void stopElevator() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
}

void openDoor() {
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(1000);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}
