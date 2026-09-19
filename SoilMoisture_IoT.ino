#include "AdafruitIO_WiFi.h"

// Replace with your Adafruit IO credentials
#define IO_USERNAME  "your_io_username"     // Adafruit IO Username
#define IO_KEY       "your_io_key"          // Adafruit IO Key

// Replace with your WiFi credentials
#define WIFI_SSID    "your_wifi_ssid"       // Wi-Fi SSID
#define WIFI_PASS    "your_wifi_password"   // Wi-Fi Password

// Pin for Soil Moisture Sensor (Analog pin)
#define MOISTURE_SENSOR_PIN 34  // GPIO 34 for analog input (so the sensor can read values)

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);  // Adafruit IO Wi-Fi setup

// Create a feed to send soil moisture data to Adafruit IO
AdafruitIO_Feed *soil_moisture = io.feed("soil_moisture");

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");  // Wait while ESP32 connects to Wi-Fi
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi!");

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Wait for the connection to establish
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");  // Wait while ESP32 connects to Adafruit IO
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to Adafruit IO!");
}

void loop() {
  // Run the Adafruit IO loop to maintain the connection and handle feed data
  io.run();

  // Read the analog value from the soil moisture sensor (pin 34)
  int moisture_value = analogRead(MOISTURE_SENSOR_PIN);

  // Print the raw sensor value to the serial monitor for debugging
  Serial.print("Raw Soil Moisture Value: ");
  Serial.println(moisture_value);

  // Map the raw sensor value to a percentage (0 to 100) to represent soil moisture
  int moisture = map(moisture_value, 4095, 2700, 0, 100);  // Adjust according to sensor calibration
  Serial.print("Mapped Moisture Percentage: ");
  Serial.println(moisture);

  // Send the moisture value to Adafruit IO feed
  soil_moisture->save(moisture);

  // Wait for 5 seconds before the next reading
  delay(5000);
}

