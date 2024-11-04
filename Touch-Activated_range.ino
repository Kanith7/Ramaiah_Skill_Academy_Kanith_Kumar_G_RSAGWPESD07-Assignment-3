// Define pins for ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;

// Define pin for push button (simulating touch sensor)
const int buttonPin = 4;

// Define pins for 7-segment display segments
const int segmentPins[] = {5, 6, 7, 8, 9, 10, 11};

// Segment encoding for displaying numbers on 7-segment (Common Cathode)
const byte digitSegments[10] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};

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
    // Take a distance measurement
    int distance = measureDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    // Display the distance on the 7-segment display (displaying only units digit)
    displayDigit(distance % 10);

    // Hold the display for 5 seconds
    delay(5000);

    // Clear the display
    clearDisplay();
  }
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
  if (digit < 0 || digit > 9) return;  // Ensure valid digit

  // Light up the segments based on the digit
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
