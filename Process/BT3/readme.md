# Process Signaling in C

## Overview
This project demonstrates inter-process communication using signals in C. A parent process creates a child process and then sends a `SIGUSR1` signal to the child after a delay. The child process defines a custom signal handler to handle `SIGUSR1`, print a message, and then terminate.

## Requirements
- Basic knowledge of C programming
- Understanding of process creation using `fork()`
- Familiarity with signals and signal handling in Linux

## Execution Flow
1. The parent process creates a child process using `fork()`.
2. The child process registers a signal handler for `SIGUSR1`.
3. The child enters an infinite loop, waiting for the signal.
4. The parent process sleeps for 3 seconds and then sends `SIGUSR1` to the child.
5. Upon receiving `SIGUSR1`, the child executes its signal handler, prints a message, and exits.
6. The parent waits for the child process to terminate and prevents it from becoming a zombie.

## Key Functions Used
- `fork()`: Creates a new child process.
- `signal()`: Registers a custom handler for `SIGUSR1`.
- `kill()`: Sends `SIGUSR1` to the child process.
- `wait()`: Ensures the parent waits for the child to terminate.

## Directory Structure
```
.
├── bin
│   └── main
├── inc
├── lib
├── Makefile
├── obj
│   └── main.o
└── src
    └── main.c
```

## How to Compile and Run
1. Navigate to the project directory.
2. Use `make` to compile the program.
3. Run the program using `./bin/main`.

This example provides a simple demonstration of process signaling, showcasing how signals can be used for inter-process communication.

