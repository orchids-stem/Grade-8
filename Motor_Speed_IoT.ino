#include <AdafruitIO_WiFi.h>  // Library to connect Adafruit IO with WiFi
#include <WiFi.h>             // ESP32 WiFi library

/******** Adafruit IO Config ***********/
#define IO_USERNAME    "your_username"  // Replace with your Adafruit IO username
#define IO_KEY         "your_aio_key"   // Replace with your Adafruit IO key

/******** WiFi Config **************/
#define WIFI_SSID       "your_wifi_ssid"    // Your WiFi SSID
#define WIFI_PASS       "your_wifi_password" // Your WiFi password

/*********** Motor Pin (PWM) *************/
#define MOTOR_PIN 13  // GPIO 13 for controlling motor speed (PWM)

/******** Adafruit IO Setup ************/
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the Adafruit IO feed for motor speed control
AdafruitIO_Feed *motor_speed_feed = io.feed("motor_speed");

void setup() {
  // Start the serial connection
  Serial.begin(115200);

  // Initialize motor pin as output (PWM)
  pinMode(MOTOR_PIN, OUTPUT);

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Set up a message handler for when feed data is received
  motor_speed_feed->onMessage(handleMessage);

  // Wait for a connection to Adafruit IO
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // We're connected!
  Serial.println();
  Serial.println("Connected to Adafruit IO!");
}

void loop() {
  // io.run() is required to process Adafruit IO messages
  io.run();
}

// Function to handle received feed data
void handleMessage(AdafruitIO_Data *data) {
  // Print the received value (motor speed) to the Serial Monitor
  Serial.print("Received motor speed: ");
  Serial.println(data->value());

  // Map the received data (0 to 100) to PWM range (0 to 255)
  int motorSpeed = map(data->toInt(), 0, 100, 0, 255);

  // Set the motor speed using PWM (0-255)
  analogWrite(MOTOR_PIN, motorSpeed);

  // Print the motor speed to the Serial Monitor for debugging
  Serial.print("Motor speed set to: ");
  Serial.println(motorSpeed);
}
