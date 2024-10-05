# Stopwatch with Dual Mode (Increment and Countdown) Using ATmega32 and Seven-Segment Display

![Screenshot 2024-09-10 174814](https://github.com/user-attachments/assets/825d4957-2c44-4854-b41d-4ded19878dfd)

## Project Overview

This project involves designing and implementing a versatile digital stopwatch using the ATmega32 microcontroller and six multiplexed seven-segment displays. It features two operational modes: Increment Mode (counting up) and Countdown Mode (counting down), with additional functionalities for user interaction and time management.

## Features

- **Increment Mode (Default):**
  - Counts upwards from zero.
  - Displays hours, minutes, and seconds on six seven-segment displays.
  
- **Countdown Mode:**
  - Counts downwards from a user-defined start time.
  - Activates a buzzer when the countdown reaches zero.

- **User Controls:**
  - **Reset Function:** Resets the time to zero in both modes.
  - **Pause Function:** Pauses the stopwatch, holding the current time.
  - **Resume Function:** Continues counting from the paused time.
  - **Mode Toggle:** Switches between increment and countdown modes.
  - **Increment and Decrement Buttons:** Adjust seconds, minutes, and hours for precise time settings.

## Technical Details

- **Microcontroller:** ATmega32 (16 MHz clock frequency)
- **Displays:** Six multiplexed common anode seven-segment displays
- **Timer Configuration:** Timer1 configured in CTC (Clear Timer on Compare Match) mode for accurate time counting.
- **Interrupts:**
  - External and internal interrupts with both falling and rising edge detection for enhanced functionality.
  
## How to Use

1. **Setup:**
   - Connect the hardware components as described in the project documentation.

2. **Operation:**
   - Use the mode toggle button to switch between Increment and Countdown modes.
   - Adjust time settings using the increment and decrement buttons.
   - Start, pause, and resume operations using the respective buttons.

3. **Countdown Mode:**
   - Pause the timer if needed.
   - Toggle to Countdown Mode.
   - Set the desired countdown start time using the adjustment buttons.
   - Resume the countdown and wait for the buzzer alert upon completion.

## Installation

1. **Hardware Setup:**
   - Assemble the circuit as per the provided schematic diagram.

2. **Software:**
   - Compile the code using an AVR-compatible compiler.
   - Upload the code to the ATmega32 microcontroller.

## Example

![Screenshot 2024-09-10 181658](https://github.com/user-attachments/assets/894abe8f-1a09-4420-b3db-aab2520cb465)

---

**Feel free to fork this repository, contribute, or raise issues if you encounter any problems. Happy coding!**
