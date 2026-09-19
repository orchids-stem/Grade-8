#include "AdafruitIO_WiFi.h"

// Adafruit IO credentials
#define IO_USERNAME  "Geo__"
#define IO_KEY       "aio_Ngzr48I0DJ3LOv5vjif64IkQNFNt"

// Wi-Fi credentials
#define WIFI_SSID    "K12-Internal WiFi"
#define WIFI_PASS    "K12@techno"

// Relay pin
#define RELAY_PIN 15

// Create Adafruit IO connection
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Adafruit IO feed
AdafruitIO_Feed *motor = io.feed("motor");

void setup() {
  pinMode(RELAY_PIN, OUTPUT);

  // Fan OFF initially (this relay is active-LOW, so HIGH = OFF here)
  digitalWrite(RELAY_PIN, HIGH);

  Serial.begin(115200);
  Serial.println("Connecting to Adafruit IO...");

  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Connected to Adafruit IO!");

  motor->onMessage(handleMotor);
}

void loop() {
  io.run();  // Keep connection alive
}

// Function to receive ON/OFF commands
void handleMotor(AdafruitIO_Data *data) {
  int command = data->toInt();

  Serial.print("Received: ");
  Serial.println(command);

  if (command == 1) {
    digitalWrite(RELAY_PIN, LOW);   // Active-LOW relay: LOW energizes it
    Serial.println("Fan ON");
  }
  else if (command == 0) {
    digitalWrite(RELAY_PIN, HIGH);  // HIGH de-energizes it
    Serial.println("Fan OFF");
  }
}