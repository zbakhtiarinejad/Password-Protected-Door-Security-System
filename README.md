# Password-Protected-Door-Security-System

This system secures access by requiring a valid password entry before actuating a simulated door lock. It integrates user input, visual status prompts, audio alerts, and mechanical actuation into a single microcontroller workflow.
<img width="1087" height="631" alt="Screenshot 2026-11-12 163202" src="https://github.com/user-attachments/assets/5ab6a583-ebad-483d-a8da-cf7121b54105" />


## How It Works

1. **PIN Entry:** Users enter a numeric or alphanumeric passcode using a 4x4 matrix keypad.
2. **Visual Feedback:** A 16x2 I2C LCD display guides the user through the authentication process, showing prompts, masked or active input, and access status messages (such as `"Wrong Password! Try Again..."`).
3. **Authentication & Actuation:** 
   * **Valid Password:** The Arduino Uno sends a PWM signal to rotate the micro servo motor, simulating the unlocking of a deadbolt or latch.
   * **Invalid Password:** The servo remains in the locked position, and the LCD alerts the user to retry.
4. **Audio Alerts:** A piezo buzzer generates distinct tones to confirm key presses, signal successful access, or warn of an unauthorized entry attempt.

## Hardware Components

* **Microcontroller:** Arduino Uno R3
* **Input Interface:** 4x4 Matrix Keypad
* **Display:** 16x2 LCD with I2C Interface
* **Actuator:** Micro Servo Motor (Locking Mechanism)
* **Audio Output:** Piezo Buzzer
* **Prototyping:** Breadboard and Jumper Wires

## Pin Configuration

| Component | Arduino Uno Pin | Notes |
| :--- | :--- | :--- |
| **4x4 Keypad (Rows/Cols)** | Digital Pins `2` – `9` | 8-pin digital matrix scanning |
| **Piezo Buzzer** | Digital Pin `10` | PWM/Tone audio feedback |
| **Micro Servo Motor** | Digital Pin `11` | PWM control signal |
| **16x2 I2C LCD** | Analog Pins `A4` (SDA), `A5` (SCL) | I2C serial communication |
