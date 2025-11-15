# Autonomous Car Prototype – Tinkercad Simulation

This project is a small autonomous car prototype developed in Tinkercad.
It uses an Arduino Uno and four ultrasonic sensors to detect obstacles and make basic navigation decisions in real time.

Features
• Reads distance from four directions (front, left, right, back)
• Autonomous navigation based on obstacle detection
• Automatic parking mode triggered by a button
• Motor control simulated in Tinkercad using digital pins
• Real time decision making with conditional logic

Files in this repository
• car_autonomous.ino: main program written in C++
• tinkercad_setup.png: wiring diagram exported from Tinkercad

How it works
The Arduino reads distance values using ultrasonic sensors, then chooses whether to move forward, turn, reverse, or stop. A button switches between normal driving and the parking routine.
All motor logic is programmed manually, including delays, PWM control, and direction switching.

What I learned
• Using C++ to control sensors and motors
• Understanding how real time logic works in embedded systems
• Structuring conditions so the car reacts to the environment
• Debugging and testing through simulation
• Planning the entire wiring and logic without external libraries

Next steps
• Add motor drivers for real hardware
• Implement PID or decision algorithms
• Add computer vision in a future physical version
