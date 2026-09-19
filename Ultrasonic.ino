int pingPin = 12;  // Trigger Pin of Ultrasonic Sensor
int echoPin = 13;  // Echo Pin of Ultrasonic Sensor
int cm;            // Variable to store the measured distance in centimeters

void setup() {
  Serial.begin(9600);  // Start serial communication to display results on the Serial Monitor
}

void loop() {
  long duration, cm;   // Variables to store the pulse duration and distance

  // Set the trigger pin as OUTPUT to send the ultrasonic pulse
  pinMode(pingPin, OUTPUT);
  
  // Ensure the trigger pin is LOW for 2 microseconds to clear it
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond HIGH pulse to the trigger pin to initiate a pulse
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  // Set the trigger pin LOW again
  digitalWrite(pingPin, LOW);
  
  // Set the echo pin as INPUT to receive the reflected signal
  pinMode(echoPin, INPUT);
  
  // Measure the duration of the pulse (time it takes for the echo to return)
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in centimeters using the speed of sound (29.1 µs/cm)
  cm = duration / 29 / 2;
  
  // Print the measured distance to the Serial Monitor
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  
  // Wait for 100ms before taking the next reading
  delay(100);
}
