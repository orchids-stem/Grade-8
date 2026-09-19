int relay = 15;         // Relay pin connected to GPIO 15 on ESP32
int pingPin = 12;       // Trigger pin of Ultrasonic Sensor (to send the signal)
int echoPin = 13;       // Echo pin of Ultrasonic Sensor (to receive the signal)
int cm;                 // Variable to store distance in centimeters

void setup() {
  pinMode(relay, OUTPUT);  // Set relay pin as OUTPUT to control the motor
  Serial.begin(9600);      // Start the Serial Monitor for debugging
}

void loop() {
  long duration;    // To store the time it takes for the signal to bounce back

  // Send an ultrasonic signal (trigger)
  pinMode(pingPin, OUTPUT);     // Set trigger pin to OUTPUT (send signal)
  digitalWrite(pingPin, LOW);   // Ensure the trigger pin is low
  delayMicroseconds(2);         // Small delay before sending the signal
  digitalWrite(pingPin, HIGH);  // Send a 10-microsecond pulse (start signal)
  delayMicroseconds(10);        // Wait for 10 microseconds
  digitalWrite(pingPin, LOW);   // Stop the pulse

  // Receive the reflected signal (echo)
  pinMode(echoPin, INPUT);      // Set echo pin as INPUT to receive the signal
  duration = pulseIn(echoPin, HIGH); // Measure the time it took for the signal to return

  // Convert duration to distance (in centimeters)
  cm = duration / 29 / 2;       // 29 microseconds per centimeter (divided by 2 for round-trip)

  // Print the distance value to the Serial Monitor
  Serial.print(cm);
  Serial.println(" cm");

  delay(500);   // Wait for 500ms before the next measurement

  // Control the relay based on the distance (water level)

  if (cm <= 5) {
    // If the distance is less than or equal to 5 cm, turn the motor OFF
    Serial.print("Water level is less than or equal to 5 cm, ");
    Serial.println("motor OFF");
    digitalWrite(relay, LOW); // Turn the motor OFF
  }

  else if (cm >= 4 && cm < 15) {
    // If the water level is between 4 cm and 15 cm, motor should stay OFF
    Serial.print("Water level is between 4 to 15 cm, ");
    Serial.println("motor OFF");
    digitalWrite(relay, LOW); // Keep the motor OFF
  }

  else if (cm >= 15) {
    // If the water level is 15 cm or more, turn the motor ON to fill the tank
    Serial.print("Water level is 15 cm or more, ");
    Serial.println("motor ON");
    digitalWrite(relay, HIGH); // Turn the motor ON
  }
}
