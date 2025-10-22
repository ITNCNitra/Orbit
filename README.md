# Orbit
> Web-controlled robotic claw arm

---

## Project Photo
![Claw Arm Image](/images/claw-arm.png)

## Features
- Operate the robot via Serial Monitor.
- Supports both Arduino Uno/Nano and ESP8266 platforms.
- Uses a Stepper Motor (28BYJ-48) for smooth, accurate 360-degree rotation of the arm's base.
- Controls up to 4 Standard Hobby Servos for multi-joint articulation.

---

## Hardware Overview
- **MCU :** Arduino Uno/Nano or ESP8266
- **Joint Actuators:** 3-4 Hobby Servos (for shoulder, elbow, wrist, and gripper control).
- **Base Actuator:** 1× 28BYJ-48 Stepper Motor
- **Stepper Driver:** 1× ULN2003 or ULN2803
- **Power:** Dedicated external power supply for motors

---

## Wiring Diagram

## How It Works
1. The ESP8266 boots up and initializes all servo and stepper motor pins.
2. It prints a control guide to the Serial Monitor showing which keys control each joint.
3. The user controls the arm by typing commands in the Serial Monitor (e.g., q or w to open or close the gripper).
4. The ESP8266 reads each incoming character and executes the matching motor function:
    - `moveAngle()` adjusts the servo position (arm, S2, S3, S4).
    - `stepperStep()` rotates the stepper motor base left or right.

---

## Getting Started
**Phase 1: Firmware Setup and Upload**
1. Choose the firmware file matching your hardware (`arduino.ino` for Uno/Nano or `esp8266.ino` for NodeMCU).
2. Open the file in Arduino IDE.
3. Install required libraries:
    - **For Arduino:** built-in Servo library.
    - **For ESP8266:** install ESP8266_ISR_Servo from Library Manager.
4. Connect your board via USB and select the correct port and board type.
5. Upload the sketch.

**Phase 2: Serial Control Test and Operation**
1. Wire up all servos and the stepper motor according to the defined pin mapping.
2. Open the **Serial Monitor** (115200 baud) after uploading.
3. The ESP prints control instructions like:
    ```
    Controls: 
    arm: q(open) w(close) 
    S2: a(backward) s(forward) 
    S3: z(down) x(up) 
    Stepper: o(left) p(right)
    ```
4. Type the corresponding keys in the Serial Monitor to move each joint or rotate the base.
5. Observe servo and stepper responses in real-time — no Wi-Fi or web interface required.

## Contribute
Want to improve this project? Contributions are welcome!

1. Fork this repository
2. Edit the code or docs
3. Submit a Pull Request

## Lincense
This project is open-source under the **MIT License**.  
Feel free to use, modify, and build upon it.