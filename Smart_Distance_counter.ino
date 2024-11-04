#include <SevSeg.h>

SevSeg sevseg;

const int trigPin = 9;
const int echoPin = 10;
const int touchPin = 2;

long duration;
float distance;
int counter = 0;

void setup() {
  // Setup pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(touchPin, INPUT_PULLUP);

  // Setup 7-segment display
  byte numDigits = 2;        // Number of digits in the display
  byte digitPins[] = {3, 4}; // Digits connected to pins 3 and 4
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; // a to g pins

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Distance in cm

  // Check if the object is within the specified distance (e.g., 10 cm)
  if (distance < 10) {
    counter++;
    delay(500); // Simple debounce and delay to prevent rapid counting
  }

  // Check if the touch sensor is activated to reset the counter
  if (digitalRead(touchPin) == LOW) {
    counter = 0;
    delay(500); // Debounce delay
  }

  // Display the counter on the 7-segment display
  sevseg.setNumber(counter);
  sevseg.refreshDisplay();
}
