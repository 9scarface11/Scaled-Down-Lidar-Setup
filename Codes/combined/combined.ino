#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

Servo Servo_horizontal;
Servo Servo_vertical;
int count = 0;
int h_start = 65;  // horizontal sweep start (pehle vert_offset)
VL53L0X sensor;
const int SENSOR_OFFSET_MM = 30;
int manual_vertical_drift = 10;    // Angle we're attaching servo2 at
int manual_horizontal_drift = 30;  // Approximations to get point clouds

void setup() {
  Serial.begin(115200);

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
    Serial.println("# Failed to detect and initialise TOF sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(20000);

  Servo_horizontal.attach(9, 500, 2500);
  Servo_vertical.attach(10, 500, 2500);
  Servo_horizontal.write(h_start);
  Servo_vertical.write(0);
  delay(500);

  Serial.print("# v_drift=");
  Serial.print(manual_vertical_drift);
  Serial.print(",h_drift=");
  Serial.println(manual_horizontal_drift);
  Serial.println("# pan,tilt,dist_mm");
}

int get_dist() {
  uint16_t raw_dist = sensor.readRangeSingleMillimeters();
  if (sensor.timeoutOccurred() || raw_dist >= 8000) return -1;  // invalid
  int calibrated_dist = (int)raw_dist - SENSOR_OFFSET_MM;
  if (calibrated_dist < 0) calibrated_dist = 0;
  return calibrated_dist;
}

void logger(int pan, int tilt, int dist) {
  Serial.print(pan);
  Serial.print(",");
  Serial.print(tilt);
  Serial.print(",");
  Serial.println(dist);
}

void loop() {
  //if (count == 0) {
   // while (true);}

  Servo_vertical.write(count);
  delay(150);
  for (int pos = h_start; pos <= 180; pos++) {
    Servo_horizontal.write(pos);
    delay(25);
    logger(pos, count, get_dist());  // move ke BAAD padho
  }
  count += 10;

  Servo_vertical.write(count);
  delay(150);
  for (int pos = 180; pos >= h_start; pos--) {
    Servo_horizontal.write(pos);
    delay(25);
    logger(pos, count, get_dist());
  }
  count += 10;

  if (count >= 180) {
    Serial.println("# DONE");
    while (true)
      ;
  }
}