//Microcontroller code below this line

//Distance Sensor code below this line. Distance value will be stored as variable distance_sensed with type float
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

float distance_sensed;   // distance in meters

void setup()
{
  Serial.begin(115200);

  // Start I2C on ESP32
  Wire.begin(21, 22);
  Wire.setClock(400000);

  delay(1000);

  Serial.println("Starting sensor...");

  sensor.setTimeout(500);

  if (!sensor.init())
  {
    Serial.println("Sensor failed to initialize!");
    while (1);
  }

  Serial.println("Sensor initialized successfully!");

  sensor.startContinuous();
}

void loop()
{
  uint16_t distance_mm = sensor.readRangeContinuousMillimeters();

  if (!sensor.timeoutOccurred())
  {
    distance_sensed = distance_mm / 1000.0;   // convert mm → meters

    Serial.print("Distance sensed (m): ");
    Serial.println(distance_sensed);
  }
  else
  {
    Serial.println("Sensor timeout!");
  }

  delay(200);
}
//UI code below this line. This block will accept variable distance_sensed with type float
