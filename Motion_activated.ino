// Define pins
const int pir = 12;     // PIR sensor output pin
const int buzzer = 13;  // Buzzer pin

void setup() {
  pinMode(pir, INPUT);      // Set PIR sensor as input
  pinMode(buzzer, OUTPUT);  // Set buzzer as output

  Serial.begin(9600);          // Initialize Serial Monitor
}

void loop() {
  int motionState = digitalRead(pir);  // Read PIR sensor state

  if (motionState == HIGH) {              // If motion is detected
    digitalWrite(buzzer, HIGH);        // Turn on the buzzer
    Serial.print("Motion detected at: ");
    Serial.println(millis() / 1000);      // Log timestamp in seconds since start
    delay(1000);                          // Buzzer delay for 1 second
  } else {
    digitalWrite(buzzer, LOW);         // Turn off the buzzer if no motion
  }
}
