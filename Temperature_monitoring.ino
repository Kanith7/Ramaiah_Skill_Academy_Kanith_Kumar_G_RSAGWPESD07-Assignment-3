#include <DHT.h>

#define DHTPIN 11           // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT22      // Define the type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

const float temperatureThreshold = 30.0; // Threshold temperature in Celsius

void setup() {
  Serial.begin(9600);       // Initialize Serial Monitor
  dht.begin();              // Start DHT sensor
}

void loop() {
  float temperature = dht.readTemperature(); // Read temperature in Celsius

  if (isnan(temperature)) {  // Check if the reading is valid
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check if temperature exceeds threshold
  if (temperature > temperatureThreshold) {
    Serial.println("Warning: Temperature exceeds threshold!");
  }

  delay(2000); // Wait 2 seconds before the next reading
}
