--------------------Custom Lidar--------------------------------------

I am working on a self project, making a lidar of my own.

-Components used:
  Arduino Nano
  VL530LX Time of Flight sensor
  SG90 Servo

-Progress till now:
  The prototyping is done in Solidworks. 
  I had to make a custom slip ring, because of the problem that will arise, where the sensor's wires might cause problem because of torsion.
  Sensor Calibration is done.
  A circuit check is being done.

-Next Steps:
  I am working on writing Arduino Code for Sensor Sweep, integrating Servo and Sensor.
  For converting sensor data into Point Clouds, Angle Rotated, and distance will be converted to Cartesian Numbers, and will be plotted accordingly.

-Future Plans:
  Integrating MPU6050 and adding state estimation, using Localization and Odometry backed by IMU.

Further Plans:
Integrating this whole system with an RC car.
