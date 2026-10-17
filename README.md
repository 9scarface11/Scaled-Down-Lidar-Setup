
# Custom LiDAR

https://github.com/user-attachments/assets/d46394fd-c32c-43c1-b5be-7fa9b66bd1a0

https://github.com/user-attachments/assets/5425dd05-36e1-41d0-8f0b-0dcabc7de7f0

A DIY 3D LiDAR built from a time-of-flight sensor on a pan–tilt servo mount. The sensor sweeps a scene, and every (pan angle, tilt angle, distance) reading is converted into a 3D point.

## Hardware

| Component | Role |
|---|---|
| Arduino Nano | Controls the servos, reads the sensor, streams data over serial |
| Arduino Uno | Controls the servos, reads the sensor, streams data over serial |
| VL53L0X ToF sensor | Distance measurement (I2C) |
| 2× SG90 servo | Pan (horizontal) and tilt (vertical) motion |
| Buck converter | Stable 5 V supply for the servos |
| MPU6050 *(planned)* | IMU for orientation / state estimation |

**Wiring:** pan servo on D9, tilt servo on D10, ToF on I2C (A4/A5). Servos run from the buck converter's 5 V, the Nano is powered over USB, and all grounds are shared.

## Status

- [x] Servos connected and working
- [x] Sensor and servos working together
- [x] First draft of sensor data collected
- [x] 3D sweeping motion achieved
- [x] Mounting TOF on servos
- [x] Recording sensor data 
- [ ] ToF sensor calibration (in progress)
- [x] Convert CSV data to a 3D point cloud
- [ ] IMU integration
- [ ] Mount on an RC car

## Recent Upgrades
Shifted to Arduino Uno

## How it works

The Nano sweeps the servos and sends one CSV line per reading:

```text
pan,tilt,dist_mm
```

Each reading is converted to Cartesian coordinates, with pan angle θ, tilt angle φ and distance d:

```text
x = d · cos(φ) · cos(θ)
y = d · cos(φ) · sin(θ)
z = d · sin(φ)
```

The points are then plotted as a 3D point cloud with Matplotlib.

## Repository structure

```text
custom-lidar/
├── README.md
├── Codes/
│   ├── 3-D sweeping_motion/# Sweeping
│   ├── combined/
|          ├── combined/    # Both sensor and servo integrated
│   └── Vl53l0x_setup/      # TOF setup and calibration
|
├── Point Cloud Files/
|          ├── file1.ply/             # python script for recording scanner and servo values
|          ├── file2.ply/
|
├── Point Cloud Raw/
|          ├── logger.py/             # python script for recording scanner and servo values
|          ├── csv/                   # (planned) recorded scans as CSV
└── CAD/                 # For prototyping design
```

See [`Codes/3d_sweep`](Codes/3d_sweep) for the sweeping code.

## Roadmap

**Next:** convert the CSV points into a 3D point cloud using Matplotlib or similar Python libraries.

**Later:** integrate the MPU6050 and add state estimation (localization and odometry backed by the IMU).

**Eventually:** integrate the whole system with an RC car.
