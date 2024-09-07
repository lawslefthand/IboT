# IboT
Codebase for Ibot projects.

Bots made by us:

**************

Resh - Robo Wrestling (Sumo) Bot
Resh is a sumo wrestling robot built using the ESP-IDF framework on the ESP32, designed for robo wrestling competitions. It leverages the power of FreeRTOS for independent, parallel control of its left and right wheel sets, ensuring quick and precise movements during combat. The bot is equipped with an L298N motor driver to power the motors efficiently and is programmed entirely using C within the ESP-IDF environment.

Key Features:
ESP32 Microcontroller: Utilizes the dual-core ESP32 for advanced processing.
FreeRTOS for Parallel Computing: Separate tasks for left and right wheels to ensure fast response.
L298N Motor Driver: Handles the motors efficiently for robust control.
Autonomous Behavior: Designed for sumo wrestling competitions with automated strategies.

*************

Pandara's Box - Competitive Line-Following Robot
Pandara's Box is a line-following robot developed for the "Search and Destroy" competition at COEP MindSpark. This bot is built on the STM32 Nucleo-F030R8 and uses digital IR sensors to detect lines and intersections. It features advanced detection of T-junctions (left, right, and straight) and inverted color patterns, ensuring it can navigate complex tracks.

Key Features:
STM32 Nucleo-F030R8 Microcontroller: Low-cost, efficient MCU running ARM CMSIS standard.
Digital IR Sensors: Optimized for accurate line and intersection detection.
Advanced Junction Detection: Recognizes T-junctions (left, right, straight) for smooth transitions.
Inverted Color Detection: Capable of handling both normal and inverted tracks (black on white, and white on black).
Coded in C using CMSIS: Built using ARM's CMSIS standard in STM32CubeIDE for high performance.


