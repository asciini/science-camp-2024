/*
  HS300x - Read Sensors

  This example reads data from the on-board HS300x sensor of the
  Nano 33 BLE Sense and prints the temperature and humidity sensor
  values to the Serial Monitor once a second.

  The circuit:
  - Arduino Nano 33 BLE Sense R2

  This example code is in the public domain.
*/

#include <Arduino_HS300x.h>
#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!HS300x.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
}

void loop() {

  
  // read all the sensor values
  float temperature = HS300x.readTemperature();
  float humidity    = HS300x.readHumidity();

  // Check if a color reading is available.
  while (!APDS.colorAvailable()) {
    delay(5);
  }

  int r, g, b, a;

  // Read the color.
  APDS.readColor(r, g, b, a);

  float color = APDS.readColor(r, g, b, a);
  float brightness = (0.21 * r) + (0.72 * g) + (0.07 * b); // subjective brightness of rgb values

  // print each of the sensor values
  Serial.println("SENSOR_START{\"temp\":\"" + String(temperature) + "\",\"humidity\":\"" + String(humidity) + "\",\"pressure\":\"123\",\"microphone\":\"123\",\"brightness\":\"" + String(brightness) + "\"}SENSOR_END");
  Serial.println();
  // wait 1 second to print again
  delay(1000);
}
