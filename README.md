# Matrix Operations Simulator

## Overview
This project is a **Matrix Operations Simulator** implemented in C, inspired by the Octave programming environment. It provides various matrix manipulation functionalities such as addition, multiplication, transposition, resizing, and more. The program is designed for efficient dynamic memory management and modularized code structure.

## Features
- Dynamic allocation of matrices in memory
- Matrix addition, multiplication (standard and Strassen algorithm)
- Matrix transposition and resizing
- Raising a matrix to a power using logarithmic exponentiation
- Sorting matrices by sum of elements
- Memory management (allocation, deallocation, and efficient resizing)

## Project Structure
The project is divided into several files to ensure a modular and well-structured implementation:

### **1. `main.c`**
This file contains the **entry point** of the program and manages user input. It initializes the necessary data structures and contains a `switch` statement that handles different matrix operations.

### **2. `matrix.c` & `matrix.h`**
These files implement and define core matrix operations:
- `modulo()` - Ensures correct calculations when handling negative numbers.
- `alloc_matrix()` - Dynamically allocates memory for a new matrix.
- `read_matrix()` - Reads matrix elements from input.
- `free_matrix()` - Frees allocated memory for a matrix.
- `create_transpose()` - Computes the transpose of a given matrix.
- `multiply()` - Performs matrix multiplication.
- `summ()` - Computes the sum of all elements in a matrix.
- `swap_matrices()` - Swaps two matrices in the array.
- `swap_numbers()` - Helper function for swapping two numbers.
- `redim()` - Redimensions a matrix based on user input.
- `rise_power()` - Raises a matrix to an exponent using logarithmic multiplication.

### **3. `case.c` & `case.h`**
These files handle specific user commands and ensure proper input handling:
- `check_command()` - Validates if the user input matches available commands.
- Each implemented command makes use of functions from `matrix.c` for efficient execution.

### **4. `my_octave.c`**
This file acts as an **entry script** that integrates the functionalities from the `matrix.c` and `case.c` files, ensuring seamless command execution.

### **5. `Makefile`**
The `Makefile` is used for compilation and provides automation for building and cleaning the project:
- `make` - Compiles the program and generates an executable named `my_octave`.
- `make clean` - Removes generated object files and executables.

## Compilation and Execution
To compile the project, simply run:
```sh
make
```
This will generate an executable called `my_octave`. You can then run the program using:
```sh
./my_octave
```

## Usage
The program accepts commands via standard input to manipulate matrices dynamically. The supported operations include:
- **L**: Load a matrix
- **D**: Get matrix dimensions
- **P**: Print a matrix
- **C**: Resize a matrix
- **M**: Multiply two matrices
- **O**: Sort matrices
- **T**: Transpose a matrix
- **R**: Raise a matrix to a power
- **F**: Free a matrix from memory
- **Q**: Quit the program and free all resources

## Memory Management
The project efficiently manages memory using **dynamic allocation** for matrices. Matrices are stored in dynamically resizable arrays that grow as needed and shrink when matrices are deleted, ensuring optimal memory usage.

