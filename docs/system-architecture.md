# System Architecture

- **Controller:** Arduino
- **Sensors:** Two photoresistors (A0 = right, A1 = left)
- **Actuator:** Servo motor on pin 11
- **Algorithm:** Servo moves toward the brighter photoresistor; resets if overall light < 600
