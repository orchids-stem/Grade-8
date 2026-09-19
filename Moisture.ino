int sensor_pin = 35;    // Pin where the soil moisture sensor is connected
int output_value;       // Raw analog value from the sensor
int moisturelevel;      // Mapped moisture level as percentage

void setup() {
  Serial.begin(9600);          // Start serial communication at 9600 baud rate
  Serial.println("Reading From the Sensor...");
  delay(2000);                 // Small delay before starting sensor readings
}

void loop() {
  output_value = analogRead(sensor_pin);    // Read the analog value from the sensor
  moisturelevel = map(output_value, 4095, 1000, 0, 100);  // Map the raw value to moisture level in percentage

  // Display the moisture level
  Serial.print("Moisture: ");
  Serial.print(moisturelevel);
  Serial.println("%");

  delay(1000);    // Delay before the next reading (1 second)
}
