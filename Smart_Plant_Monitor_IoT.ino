#include "AdafruitIO_WiFi.h"

// Replace with your Adafruit IO credentials
#define IO_USERNAME  "your_io_username"     // Adafruit IO Username
#define IO_KEY       "your_io_key"          // Adafruit IO Key

// Replace with your Wi-Fi credentials
#define WIFI_SSID    "your_wifi_ssid"       // Wi-Fi SSID
#define WIFI_PASS    "your_wifi_password"   // Wi-Fi Password

// Pin for Soil Moisture Sensor and Relay
#define relay 15              // Pin connected to the relay
#define sensor_pin 35         // Pin connected to the soil moisture sensor

// Create an instance of AdafruitIO_WiFi for ESP32
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Create feeds for soil moisture and relay status
AdafruitIO_Feed *soil_moisture = io.feed("soil_moisture");
AdafruitIO_Feed *Relay_Control = io.feed("Relay_Control");

int output_value;            // To store the raw analog value from the sensor
int moisturelevel;           // To store the mapped moisture level in percentage

void setup() {
  Serial.begin(9600);        // Start serial communication at 9600 baud rate
  pinMode(relay, OUTPUT);    // Set the relay pin as output
  
  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to Wi-Fi!");

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO...");
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to Adafruit IO!");

  // Notify when the program starts
  Serial.println("Reading from the sensor...");
  delay(2000);               // Delay for 2 seconds before starting the sensor readings
}

void loop() {
  // Read the raw analog value from the sensor
  output_value = analogRead(sensor_pin);

  // Map the raw value (4095-1000) to a moisture level percentage (0-100)
  moisturelevel = map(output_value, 4095, 1000, 0, 100);

  // Print the moisture level to the serial monitor
  Serial.print("Moisture: ");
  Serial.print(moisturelevel);
  Serial.println("%");

  // Send the moisture level to Adafruit IO
  soil_moisture->save(moisturelevel);

  // Check if moisture level is below 25%
  if (moisturelevel < 25) {
    digitalWrite(relay, HIGH);  // Turn the motor ON
    Relay_Control->save(1);        // Send relay status (1 = ON) to Adafruit IO
  } 
  else {
    digitalWrite(relay, LOW);   // Turn the motor OFF
    Relay_Control->save(0);        // Send relay status (0 = OFF) to Adafruit IO
  }

  // Send relay status to Adafruit IO
  Serial.print("Relay Status: ");
  Serial.println(digitalRead(relay) ? "ON" : "OFF");

  // Wait for 1 second before the next reading
  delay(1000);
}

