# 3D Rotating Cube ASCII Animation

This project is a simple C program that renders a 3D rotating cube using ASCII characters in the terminal. The cube rotates in real-time, and the animation is achieved by manipulating a 2D buffer and simulating depth using a z-buffer.

NB : The entirety of the code defining rotation is based on quaternions properties. You can read this [article](https://graphics.stanford.edu/courses/cs348a-17-winter/Papers/quaternion.pdf) to understand `quaternion.c`.

![im](./images/spin.png)
## Table of Contents

1. [Features](#features)
2. [Code Overview](#code-overview)
   - [Dependencies](#dependencies)
   - [Key Components](#key-components)
3. [How to Compile and Run](#how-to-compile-and-run)
   - [Compilation](#compilation)
   - [Running the Program](#running-the-program)
4. [Customization](#customization)
5. [Example Output](#example-output)
6. [License](#license)
7. [Contributing](#contributing)
8. [Acknowledgments](#acknowledgments)

## Features

- **3D Rotation**: The cube rotates around a custom axis in 3D space.
- **Z-Buffering**: Depth is simulated using a z-buffer to ensure correct rendering of overlapping surfaces.
- **Cross-Platform**: The code includes a custom `usleep` implementation for Windows, making it compatible with both Unix-based systems and Windows.
- **Customizable Parameters**: You can adjust the cube size, rotation speed, and other parameters to modify the animation.

## Code Overview

### Dependencies

- **Standard Libraries**: The code uses standard C libraries like `<stdio.h>` and `<string.h>`.
- **Custom Quaternion Library**: The program relies on a custom `quaternion.h` library for vector and rotation operations. Ensure this library is available in your project.

### Key Components

1. **Global Variables**:
   - `width` and `height`: Define the size of the terminal buffer.
   - `zBuffer`: Stores depth information to handle overlapping surfaces.
   - `buffer`: Stores the ASCII characters to be displayed.
   - `distanceFromCam`, `K1`, `resolution_ratio`, `speed`, `horizontalOffset`, `cubeWidth`: Control the cube's position, size, and rotation speed.

2. **`update_surface` Function**:
   - Updates the buffer with the correct ASCII character based on the cube's rotation and depth.
   - Uses the z-buffer to ensure that only the closest surfaces are rendered.

3. **Main Loop**:
   - Clears the buffer and z-buffer at the start of each frame.
   - Rotates the cube and updates the buffer with the new positions of the cube's surfaces.
   - Prints the buffer to the terminal, creating the animation effect.
   - Pauses briefly between frames to control the animation speed.

### Cross-Platform Support

- **Unix-Based Systems**: Uses the standard `usleep` function from `<unistd.h>`.
- **Windows**: Implements a custom `usleep` function using Windows API calls.

## How to Compile and Run

### Compilation

To compile the program :
- use a C compiler like `gcc`.
- modify the `Makefile` if needed
- run the following commands

```
make
./spinning_cube
```
