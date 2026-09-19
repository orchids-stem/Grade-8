int relay = 15; // Pin where the relay is connected

void setup() {
  pinMode(relay, OUTPUT); // Setting the relay pin as output
}

void loop() {
  digitalWrite(relay, HIGH); // Relay ON
  delay(3000);               // Wait for 3 seconds
  digitalWrite(relay, LOW);  // Relay OFF
  delay(1000);               // Wait for 1 second
}
