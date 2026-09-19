#include <AdafruitIO_WiFi.h>  // Library to connect Adafruit IO with WiFi
#include <WiFi.h>             // ESP32 WiFi library

/******** Adafruit IO Config ***********/
#define IO_USERNAME    "your_username"  // Replace with your Adafruit IO username
#define IO_KEY         "your_aio_key"   // Replace with your Adafruit IO key

/******** WiFi Config **************/
#define WIFI_SSID       "your_wifi_ssid"    // Your WiFi SSID
#define WIFI_PASS       "your_wifi_password" // Your WiFi password

/*********** Relay Pin *************/
#define RELAY_PIN 15  // GPIO 15 is typically used for controlling a relay (replace with your pin number)

/******** Adafruit IO Setup ************/
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the Adafruit IO feed for relay control
AdafruitIO_Feed *Relay_Control = io.feed("Relay_Control");

void setup() {
  // Start the serial connection
  Serial.begin(115200);

  // Initialize relay pin as output
  pinMode(RELAY_PIN, OUTPUT);

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Set up a message handler for when feed data is received
  Relay_Control->onMessage(handleMessage);

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

  // Turn relay on or off based on the received value
  if (data->toInt() == 1) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn relay on
    Serial.println("Relay turned ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn relay off
    Serial.println("Relay turned OFF");
  }
}

