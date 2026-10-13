#include <Servo.h>

Servo Servo_horizontal;
Servo Servo_vertical;
int count = 0;
void setup() {
  Servo_horizontal.attach(9, 500, 2500);
  Servo_vertical.attach(10, 500, 2500);
  Servo_horizontal.write(0);
  Servo_vertical.write(0);
 // Signal wire connected to Digital Pin 9
}

void loop() {
  // Sweep forward from 0 to 90 degrees

  Servo_vertical.write(count);
  delay(50);
  count +=5;
  for (int pos = 0; pos <= 180; pos++) {
    Servo_horizontal.write(pos);
    delay(50);
  }
  Servo_vertical.write(count);
  delay(50);
  for (int pos = 180; pos >= 0; pos--) {
    Servo_horizontal.write(pos);
    delay(50);
  } // Brief pause at 90 degrees
  count +=5;
  // Sweep backward from 90 down to 0 degrees
  delay(50); // Brief pause at 0 degrees
  if (count >= 180) {
    while (true); // Halt execution
}
}
