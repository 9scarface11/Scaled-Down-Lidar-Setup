#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

// Calibration offset (in mm)
const int SENSOR_OFFSET_MM = 30;

void setup() {
  Serial.begin(9600);

  // I2C bus clear routine
  pinMode(A5, OUTPUT);
  for (int i = 0; i < 9; i++) {
    digitalWrite(A5, HIGH);
    delayMicroseconds(5);
    digitalWrite(A5, LOW);
    delayMicroseconds(5);
  }
  pinMode(A5, INPUT);

  Wire.begin();

  sensor.setTimeout(500);
  
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize VL53L0X sensor!");
    while (1) {} 
  }

  // High speed mode: 20ms (20000 us)
  sensor.setMeasurementTimingBudget(20000);

  // Start continuous back-to-back readings
  sensor.startContinuous();
  
  Serial.println("VL53L0X Distance Sensor Ready!");
}

void loop() {
  // Read distance in millimeters
  uint16_t raw_dist = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.println("TIMEOUT: Sensor reading lost!");
  } 
  else if (raw_dist >= 8000) {
    Serial.println("OUT OF RANGE");
  } 
  else {
    // Apply calibration offset
    int calibrated_dist = (int)raw_dist - SENSOR_OFFSET_MM;
    if (calibrated_dist < 0) calibrated_dist = 0;

    Serial.print("Calibrated Distance: ");
    Serial.print(calibrated_dist);
    Serial.println(" mm");
  }

  delay(100);
}