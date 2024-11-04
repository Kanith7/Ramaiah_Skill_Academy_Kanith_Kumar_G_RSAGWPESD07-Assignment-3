#include <SevSeg.h>  // Library to control 7-segment display

SevSeg sevseg;       // Instantiate a 7-segment object

const int trigPin = 9; 
const int echoPin = 10;

void setup() {
  Serial.begin(9600);
  
  // Setup ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // 7-segment display setup
  byte numDigits = 4;
  byte digitPins[] = {11, 12, 13, A0};  // Control pins for each digit
  byte segmentPins[] = {8, 7, 6, 5, 4, 3, 2, 1};  // Segment pins A-G, DP
  bool resistorsOnSegments = true;  // If resistors are on segment pins
  bool updateWithDelays = true;
  bool leadingZeros = false;  
  bool disableDecPoint = true;  

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
  // Measure distance
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Calculate distance in cm

  // Display distance on 7-segment
  sevseg.setNumber(distance, 0);  // Display integer distance in cm
  sevseg.refreshDisplay();  // Refresh display to update the segments
  
  delay(100);  // Update delay
}
