# Orbit
> Web-controlled robotic claw arm

---

## Project Photo


## Features
- Operate the robot from any device with a browser.
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
1. The ESP8266 connects to the local Wi-Fi network using a pre-configured SSID and password.
2. It hosts a simple webpage that displays controls for each joint.
3. When a control button is pressed, the browser sends an HTTP request (e.g., /move?joint=gripper&action=open) to the ESP8266.
4. The ESP8266 receives the command and executes the appropriate low-level motor function (either moveAngle for a servo or stepperStep for the base).

---

## Getting Started
**Phase 1: Firmware Setup and Upload**
1. Choose the firmware file matching your hardware.
2. Update Wi-Fi Credentials (ESP8266 only).
    ```cpp
    const char* ssid = "YOUR_WIFI_NAME";
    const char* password = "YOUR_WIFI_PASSWORD";
    ```
3. Install Libraries (ESP8266 only).
4. Upload the sketch to your ESP8266 using the Arduino IDE.

**Phase 2: Web Control Test and Operation**
1. Wire Up Hardware.
2. Get IP Address (e.g., http://192.168.1.100).
3. Visit that IP in a browser (e.g., http://192.x.x.x). 

## Contribute
Want to improve this project? Contributions are welcome!

1. Fork this repository
2. Edit the code or docs
3. Submit a Pull Request

## Lincense
This project is open-source under the **MIT License**.  
Feel free to use, modify, and build upon it.