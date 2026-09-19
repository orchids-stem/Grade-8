int pingPin = 12; // Trigger pin of the ultrasonic sensor
int echoPin = 13; // Echo pin of the ultrasonic sensor

void setup()
{
Serial.begin(9600); // Start serial communication

pinMode(pingPin, OUTPUT); // Set trigger pin as OUTPUT
pinMode(echoPin, INPUT); // Set echo pin as INPUT
}

void loop()
{
long duration;
float cm;

// Send a 10-microsecond pulse to the trigger pin
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);

// Measure the duration of the echo pulse
duration = pulseIn(echoPin, HIGH, 30000);

// Calculate distance in centimeters
cm = duration / 58.0;

// Display the distance on the Serial Monitor
Serial.print(cm);
Serial.println(" cm");
delay(100);
}
