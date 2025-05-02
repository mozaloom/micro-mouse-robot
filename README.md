# Micro Mouse Robot

Arduino Nano code for a micro mouse maze-solving robot using two N20 12V 200 RPM DC motors.

## Files

- `MicroMouse_Ultrasonic.ino` — 4 ultrasonic sensors (HC-SR04)  
- `MicroMouse_IR.ino` — 3 IR reflectance sensors

## Features

- Supports left-hand or right-hand rule (selectable via switch on A4)  
- Follows walls, avoids obstacles, and navigates mazes

## Hardware

- Arduino Nano  
- 2× N20 12V 200 RPM DC motors  
- Motor driver (L298N / L293D)  
- 4× HC-SR04 or 3× IR sensors  
- Toggle switch (A4)

## Notes

- Tune thresholds (`THRESH`, `IR_THRESH`) for your maze  
- Adjust motor speeds in `setMotors()`

---

MIT License