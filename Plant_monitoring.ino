int relay = 15;              // Pin connected to the relay
int sensor_pin = 35;         // Pin connected to the soil moisture sensor
int output_value;            // To store the raw analog value from the sensor
int moisturelevel;           // To store the mapped moisture level in percentage

void setup() {
  Serial.begin(9600);        // Start serial communication at 9600 baud rate
  pinMode(relay, OUTPUT);    // Set the relay pin as output
  Serial.println("Reading From the Sensor...");
  delay(2000);               // Delay for 2 seconds before starting the sensor readings
}

void loop() {
  output_value = analogRead(sensor_pin);  // Read the raw analog value from the sensor
  
  // Map the raw value (4095-1000) to a moisture level percentage (0-100)
  moisturelevel = map(output_value, 4095, 1000, 0, 100); 
  
  // Print the moisture level to the serial monitor
  Serial.print("Moisture: ");
  Serial.print(moisturelevel);
  Serial.println("%");
  
  delay(1000);  // Wait for 1 second before the next reading
  
  // If the moisture level is less than 25%, turn on the motor (relay)
  if (moisturelevel < 25) {
    digitalWrite(relay, HIGH);  // Turn the motor ON
  } 
  // If the moisture level is 25% or above, turn off the motor (relay)
  else {
    digitalWrite(relay, LOW);   // Turn the motor OFF
  }
}
