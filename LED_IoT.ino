#include <AdafruitIO_WiFi.h>  // Library to connect Adafruit IO with WiFi
#include <WiFi.h>             // ESP32 WiFi library

/******** Adafruit IO Config ***********/
#define IO_USERNAME    "your_username"  // Replace with your Adafruit IO username
#define IO_KEY         "your_aio_key"   // Replace with your Adafruit IO key

/******** WiFi Config **************/
#define WIFI_SSID       "your_wifi_ssid"    // Your WiFi SSID
#define WIFI_PASS       "your_wifi_password" // Your WiFi password

/*********** LED Pin *************/
#define LED_PIN 2  // GPIO 2 is typically used for the onboard LED on ESP32

/******** Adafruit IO Setup ************/
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the Adafruit IO feed for LED control
AdafruitIO_Feed *led_feed = io.feed("led_feed");

void setup() {
  // Start the serial connection
  Serial.begin(115200);

  // Initialize LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Set up a message handler for when feed data is received
  led_feed->onMessage(handleMessage);

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
  // Print the received value (on/off) to the Serial Monitor
  Serial.print("Received: ");
  Serial.println(data->value());

  // Turn LED on or off based on the received value
  if (data->toInt() == 1) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED on
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn LED off
  }
}

