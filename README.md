# RoboCup Junior Rescue Maze Simulator

This project is a simulator built using Unreal Engine for a robotics competition. The competition is [**RoboCup Junior Rescue Maze**](https://junior.robocup.org/rescue/) which involves constructing a robot that navigates a maze and reacts to certain environmental conditions. During the pandemic, it was impossible to meet in person, so we developed this simulator to observe how the robot behaves in a simulated environment. This allowed us to fine-tune the code before designing the electronics.

## Project Overview

### Graphical Implementation

The main level of the simulator was built using open-source models and assets from [**Quixel Megascans**](https://quixel.com/megascans). The maze is dynamically generated based on a `.json` file created by a separate Java program, which is not part of this project.

### Technical Implementation

The robot design used in the competition was divided into two main components:
- **Orientation**
- **Sensors**

The maze navigation logic was controlled by a **Raspberry Pi**, which held the map of the maze. Meanwhile, the sensor data was processed by an **STM32**, which performed more precise calculations due to its higher update frequency.

The high-level code for the STM32, programmed in **C++**, was kept consistent across both the simulator and the real-world project. The physical implementations of the sensors differed between the simulator and the actual hardware, but we simulated sensor errors (e.g., gyroscope shifting) within the graphical engine to ensure the code was stable and ready for deployment on physical hardware.

By using preprocessor macros, it was possible to compile from the same source code, using Unreal Engine files for simulation rather than the STM32 compiler.

## Key Features
- **Dynamic Maze Generation**: The maze is generated from a JSON file to replicate the dynamic nature of the competition environment.
- **Sensor Error Simulation**: The simulator includes sensor error simulations, such as gyroscope drift, to mimic real-world inaccuracies.
- **Cross-Platform Code Compatibility**: The same C++ codebase can be used in both the simulator and the physical robot, allowing for streamlined development and testing.


---

**Developers:**
- [Francesco Zanus-Fortes](https://github.com/PaesaggioSonoro)
- [Leone Bacciu](https://github.com/LeoneBacciu/)
- Bruno Baldo


