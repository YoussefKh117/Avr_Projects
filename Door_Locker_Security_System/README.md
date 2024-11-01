# Advanced Door Locker Security System

![Screenshot 2024-11-01 153948](https://github.com/user-attachments/assets/19f6b37d-3d03-4747-8d7e-33bad01be968)

## Project Overview

This project involves designing and implementing an Advanced Door Locker Security System using dual microcontrollers. The system provides secure and user-friendly access control for doors, integrating a Human-Machine Interface (HMI) and Control Electronic Control Units (ECUs) to handle password management, authentication, and automated door locking. Ideal for enhancing security in homes or businesses, the system combines hardware components such as a keypad, LCD, DC motor, PIR sensor, and EEPROM for a comprehensive security solution.

## Features

- **Password Management and Authentication:**
  - Secure password creation and validation, with storage in EEPROM.
  - Manages three attempts before triggering a security lockdown and activating a buzzer alert.

- **User Interface:**
  - LCD displays feedback and instructions, guiding users through password setup, entry, and system actions.
  - Keypad enables user input for passwords and mode selection.

- **Motorized Door Control:**
  - PWM-controlled DC motor locks/unlocks the door based on authentication.
  - Controlled with an H-Bridge, allowing bidirectional movement and secure locking.

- **Motion Detection:**
  - PIR sensor keeps the door unlocked when detecting motion, allowing safe passage.
  - Locks the door automatically once no further motion is detected.

- **Security Alert System:**
  - Activates a buzzer after three failed attempts to indicate unauthorized access.
  - Locks down the system, preventing further attempts for a specified duration.

## Hardware Components

- **Microcontrollers:** One each for HMI_ECU and Control_ECU
- **LCD Display:** Shows system messages and user prompts
- **Keypad:** For password input and mode selection
- **DC Motor & H-Bridge:** Controls the door locking mechanism
- **PIR Sensor:** Detects motion to keep the door open if someone is near
- **Buzzer:** Activates after three failed password attempts
- **EEPROM (I2C):** Stores passwords securely, retaining data after power loss

## System Architecture and Communication

- **Layered Architecture:**
  - **Application Layer (APP):** Manages user interactions, password setup, and system modes.
  - **Communication Abstraction Layer (CAL):** Manages UART and I2C communication.
  - **Microcontroller Abstraction Layer (MCAL):** Configures UART, I2C, timers, and GPIO.
  - **Library Layer (LIB):** Provides utility functions for delays and data manipulation.

- **Communication Protocols:**
  - **UART:** Connects HMI_ECU with Control_ECU for secure data exchange.
  - **I2C:** Enables EEPROM communication for password storage and retrieval.

## How It Works

1. **Initialization:** The system boots up, displaying a welcome message and guiding the user to set up or enter a password.
2. **Password Creation:** Users set and confirm a password, which is stored in EEPROM for future access.
3. **Door Unlocking:** The door unlocks when the correct password is entered, and the PIR sensor monitors motion to keep it open until no further movement is detected.
4. **Failed Attempt Handling:** After three incorrect attempts, the system activates the buzzer and initiates a one-minute lockdown.
5. **Real-Time Feedback:** The LCD provides real-time feedback on system status, such as successful entry, failed attempts, and motion detection.

## Setup and Installation

1. **Hardware Setup:**
   - Assemble the components as per the provided circuit diagram, ensuring proper connections for the LCD, keypad, DC motor, PIR sensor, buzzer, and EEPROM.

2. **Software Installation:**
   - Compile the code using an AVR-compatible compiler and upload it to the microcontrollers (HMI_ECU and Control_ECU).

## Example

![Screenshot 2024-11-01 153917](https://github.com/user-attachments/assets/3869ec8f-e879-4d32-ae1f-0931a2909fa1)

## Key Learnings

- Mastered UART and I2C communication for secure data exchange between microcontrollers and external memory.
- Developed a layered software architecture for modular and maintainable code.
- Implemented configurable drivers to adapt hardware control across different scenarios.

---

**Feel free to fork this repository, contribute, or raise issues if you encounter any problems. Happy coding!**
