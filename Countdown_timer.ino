// Define pins for ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;

// Define pin for push button (simulating the touch sensor)
const int buttonPin = 4;

// Define pins for 7-segment display segments
const int segmentPins[] = {5, 6, 7, 8, 9, 10, 11};

// Segment encoding for numbers and "E" on 7-segment display (Common Cathode)
const byte digitSegments[] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
  B01111001   // E
};

// Countdown start value
int countdownValue = 9;
const int obstacleDistance = 10; // Distance threshold in cm

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Using internal pull-up for button

  // Set segment pins as output
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  clearDisplay();  // Clear display initially
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) { // Button press detected (LOW due to pull-up)
    startCountdown();
    delay(500); // Debounce delay
  }
}

// Function to start countdown and handle obstacle detection
void startCountdown() {
  for (int i = countdownValue; i >= 0; i--) {
    // Display the current countdown value
    displayDigit(i);

    // Check for obstacle within the specified range
    if (measureDistance() <= obstacleDistance) {
      Serial.println("Obstacle detected! Resetting countdown.");
      delay(500); // Small delay to avoid bouncing
      return; // Exit the function to reset the countdown
    }

    delay(1000); // Hold each countdown value for 1 second
  }

  // If countdown completes without interruption, display "E"
  displayDigit(10); // 10 represents "E" in the digitSegments array
  delay(5000);      // Display "E" for 5 seconds
  clearDisplay();   // Clear display after showing "E"
}

// Function to measure distance using the ultrasonic sensor
int measureDistance() {
  long duration;
  int distance;

  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  return distance;
}

// Function to display a single digit on the 7-segment display
void displayDigit(int digit) {
  if (digit < 0 || digit > 10) return;  // Ensure valid digit

  // Light up the segments based on the digit or "E"
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(digitSegments[digit], i));
  }
}

// Function to clear the 7-segment display
void clearDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
}
