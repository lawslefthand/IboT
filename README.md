# IboT
Codebase for Ibot projects.

Bots made by us:

**************
![367896923-10f8b5f2-208d-4f7a-b701-85d22024adaa (1)](https://github.com/user-attachments/assets/08cb5661-e7ff-494b-9d5d-54c151e19db8)


# Resh - Robo Wrestling (Sumo) Bot

**Resh** is a sumo wrestling robot built using the ESP-IDF framework on the ESP32, designed for robo wrestling competitions. It leverages the power of FreeRTOS for independent, parallel control of its left and right wheel sets, ensuring quick and precise movements during combat. The bot is equipped with an L298N motor driver to power the motors efficiently and is programmed entirely in C within the ESP-IDF environment.

## Key Features

- **ESP32 Microcontroller**: Utilizes the dual-core ESP32 for advanced processing.
- **FreeRTOS for Parallel Operations**: Separate tasks for left and right wheels to ensure fast response.
- **L298N Motor Driver**: Handles the motors efficiently for robust control.
- **Core**: Designed for sumo wrestling competitions with automated strategies.

## Technologies Used

- **ESP-IDF**: Espressif IoT Development Framework.
- **FreeRTOS**: Real-time operating system for managing multiple tasks.
- **C Programming**: Low-level programming for performance optimization.
- **L298N Motor Driver**: Motor driver to control the left and right wheel sets.

## Hardware

1. **List**:
   - ESP32 microcontroller.
   - L298N motor driver.
   - DC motors for left and right wheel sets.
   - 11.1V RobuPro 2000 mAh batteries


## License

This project is licensed under the MIT License.


*************
![image](https://github.com/user-attachments/assets/2ce540c7-4a0a-493d-913a-5db3a254d530)

Pandara's Box - Competitive Line-Following Robot
Pandara's Box is a line-following robot developed for the "Search and Destroy" competition at COEP MindSpark. This bot is built on the STM32 Nucleo-F030R8 and uses digital IR sensors to detect lines and intersections. It features advanced detection of T-junctions (left, right, and straight) and inverted color patterns, ensuring it can navigate complex tracks.

Key Features:
1)STM32 Nucleo-F030R8 Microcontroller: Low-cost, efficient MCU running ARM CMSIS standard.
2)Digital IR Sensors: Optimized for accurate line and intersection detection.
3)Advanced Junction Detection: Recognizes T-junctions (left, right, straight) for smooth transitions.
4)Inverted Color Detection: Capable of handling both normal and inverted tracks (black on white, and white on black).
5)Coded in C using CMSIS: Built using ARM's CMSIS standard in STM32CubeIDE for high performance.


