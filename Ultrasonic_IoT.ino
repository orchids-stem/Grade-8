#include "AdafruitIO_WiFi.h"

// Replace with your Adafruit IO credentials
#define IO_USERNAME  "your_username"      // Adafruit IO Username (replace with your actual username)
#define IO_KEY       "your_aio_key"       // Adafruit IO Key (replace with your actual key)

// Replace with your Wi-Fi credentials
#define WIFI_SSID    "your_wifi_ssid"     // Wi-Fi SSID (replace with your actual Wi-Fi name)
#define WIFI_PASS    "your_wifi_password" // Wi-Fi Password (replace with your actual Wi-Fi password)

// Pin for Soil Moisture Sensor (Ultrasonic)
#define Trig 12  // GPIO 12 for trig/ping pin
#define Echo 13  // GPIO 13 for echo pin

// Create an instance of AdafruitIO_WiFi for ESP32
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Create a feed called "distance" to send distance data
AdafruitIO_Feed *distance_feed = io.feed("distance");

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Set up the ultrasonic sensor pins
  pinMode(Trig, OUTPUT); // Trigger pin
  pinMode(Echo, INPUT);  // Echo pin

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);  // Delay for 500ms to avoid overloading the serial
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi!");

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Wait for the connection to establish
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);  // Delay for 500ms to avoid overloading the serial
  }
  Serial.println();
  Serial.println("Connected to Adafruit IO!");
}

void loop() {
  // Run the Adafruit IO loop to maintain the connection
  io.run();

  // Read and calculate the distance
  long duration;
  int distance_value;
  
  // Send a pulse to trigger the sensor
  digitalWrite(Trig, LOW);  // Clear the trig pin
  delayMicroseconds(2);     // Short delay to stabilize
  digitalWrite(Trig, HIGH); // Send a 10us pulse to start measuring
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);  // Turn off the trig pin

  // Measure the time for the pulse to return
  duration = pulseIn(Echo, HIGH);

  // Calculate distance in cm (based on speed of sound: 29.1 microseconds per cm)
  distance_value = duration / 29 / 2;

  // Print the distance value to the Serial Monitor
  Serial.print("Distance Value: ");
  Serial.print(distance_value);
  Serial.println(" cm");

  // Send the distance value to Adafruit IO feed
  distance_feed->save(distance_value);

  // Wait for 500 milliseconds before the next measurement
  delay(500);  // Adjust this delay as needed (based on how frequently you want updates)
}
