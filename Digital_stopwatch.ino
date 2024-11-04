#include <LiquidCrystal.h>

// Initialize the LCD library with the pins connected to the LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
const int startStopButton = 8; // Button to start/stop the stopwatch
const int resetButton = 9;      // Button to reset the stopwatch

// Variables for stopwatch functionality
unsigned long startTime = 0;    // Variable to store the start time
unsigned long elapsedTime = 0;   // Variable to store elapsed time
bool running = false;            // State of the stopwatch

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  pinMode(startStopButton, INPUT);
  pinMode(resetButton, INPUT);
  
  // Display initial message
  lcd.print("Stopwatch");
  delay(2000);
}

void loop() {
  // Check if the start/stop button is pressed
  if (digitalRead(startStopButton) == HIGH) {
    delay(200); // Debounce delay
    if (running) {
      // Stop the stopwatch
      elapsedTime += millis() - startTime;
      running = false;
    } else {
      // Start the stopwatch
      startTime = millis();
      running = true;
    }
  }

  // Check if the reset button is pressed
  if (digitalRead(resetButton) == HIGH) {
    delay(200); // Debounce delay
    elapsedTime = 0; // Reset elapsed time
    if (!running) {
      lcd.clear();
      lcd.print("Stopwatch");
      lcd.setCursor(0, 1);
      lcd.print("Reset");
      delay(2000);
      lcd.clear();
    }
  }

  // Display the elapsed time
  if (running) {
    unsigned long currentTime = millis();
    unsigned long displayTime = elapsedTime + (currentTime - startTime);
    
    int seconds = (displayTime / 1000) % 60;
    int minutes = (displayTime / (1000 * 60)) % 60;
    int hours = (displayTime / (1000 * 3600));
    
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(hours);
    lcd.print(":");
    lcd.print(minutes < 10 ? "0" : ""); // Leading zero
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds < 10 ? "0" : ""); // Leading zero
    lcd.print(seconds);
  }
}
