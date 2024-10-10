# Car Parking Sensor Using ATmega32

![Screenshot 2024-10-11 015704](https://github.com/user-attachments/assets/786e59e2-af4a-41ab-967e-6cbc9d20766b)

## Project Overview

This project involves designing and implementing a car parking sensor system using the ATmega32 microcontroller. It helps drivers detect obstacles and avoid collisions while parking, utilizing an ultrasonic sensor and providing real-time feedback through an LCD display, LEDs, and a buzzer.

## Features

- **Ultrasonic Distance Measurement:**
  - The system uses an HC-SR04 ultrasonic sensor to measure the distance to nearby obstacles.
  
- **LCD Display:**
  - Displays the measured distance in centimeters and shows "Stop" when the distance is less than 5 cm.

- **LED Indicators:**
  - Three LEDs (Red, Green, Blue) light up based on the proximity of an obstacle:
    - **Distance <= 5 cm:** All LEDs flashing, Buzzer sounds, LCD shows "Stop."
    - **6 cm <= Distance <= 10 cm:** All LEDs ON, no buzzer.
    - **11 cm <= Distance <= 15 cm:** Red and Green LEDs ON, Blue LED OFF.
    - **16 cm <= Distance <= 20 cm:** Only Red LED ON.
    - **Distance > 20 cm:** All LEDs OFF, Buzzer OFF.

- **Buzzer Alert:**
  - The buzzer sounds when the object is too close (≤ 5 cm).

## Hardware Components

- **Microcontroller:** ATmega32
- **Ultrasonic Sensor:** HC-SR04
- **Display:** 16x2 LCD
  - **RS:** PD0
  - **Enable:** PD1
  - **R/W:** Ground (always write mode)
  - **Data Pins:** PORTC
- **LEDs:**
  - **Red LED:** Connected to PB5
  - **Green LED:** Connected to PB6
  - **Blue LED:** Connected to PB7
- **Buzzer:** Connected to PD3, activated during proximity alerts.

## Operation Description

- **Distance Measurement:** The ultrasonic sensor emits ultrasonic waves and measures the time taken for the waves to return, calculating the distance to obstacles.
- **Feedback Mechanism:** As the distance decreases, the LEDs light up and the buzzer activates based on the proximity thresholds, providing real-time feedback to the driver.
- **LCD Display:** Continuously updates to show the measured distance and alerts the driver when necessary.

## System Requirements

1. **Microcontroller:** ATmega32
2. **System Frequency:** 16 MHz
3. **Layered Model Architecture:**
   - The project should be implemented using a structured layered model architecture for better organization and modularity.

## How to Use

1. **Setup:**
   - Connect the hardware components as described in the project documentation.

2. **Operation:**
   - The system automatically measures distance and provides alerts as the car approaches obstacles.
   - The driver receives real-time feedback through the LCD, LEDs, and buzzer.

3. **Real-Time Monitoring:**
   - The LCD continuously updates to show the distance to the nearest obstacle.

## Installation

1. **Hardware Setup:**
   - Assemble the circuit as per the provided schematic diagram.

2. **Software:**
   - Compile the code using an AVR-compatible compiler.
   - Upload the code to the ATmega32 microcontroller.

## Example

![Screenshot 2024-10-11 015812](https://github.com/user-attachments/assets/531e37c4-e63f-49f6-a876-50fd2fdcf229)

---

**Feel free to fork this repository, contribute, or raise issues if you encounter any problems. Happy coding!**
