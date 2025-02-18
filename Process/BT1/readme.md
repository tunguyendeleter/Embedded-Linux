# Process Creation in C

## Overview
This project demonstrates process creation in C using `fork()`. The program creates a child process and prints its PID. The parent process waits for the child process to terminate to prevent it from becoming a zombie.

## Directory Structure
```
.
├── bin
│   └── main        # Compiled executable
├── inc             # Header files (if needed)
├── lib             # Libraries (if needed)
├── Makefile        # Build system
├── obj
│   └── main.o      # Compiled object file
└── src
    └── main.c      # Source code
```

## Code Explanation
### main.c
- Uses `fork()` to create a child process.
- The parent registers a `SIGCHLD` signal handler to wait for the child process to exit.
- The child prints its PID and exits.
- The parent prints its child’s PID and waits.

### Key Functions
- `fork()`: Creates a new process.
- `getpid()`: Returns the process ID.
- `wait()`: Waits for the child process to finish.
- `signal(SIGCHLD, handler)`: Handles child termination.

## How to Build and Run
1. Compile the program:
   ```sh
   make
   ```
2. Clean up compiled files:
   ```sh
   make clean
   ```

## Common Questions
### 1. What is a zombie process?
A zombie process is a child process that has terminated but its parent hasn’t called `wait()`, leaving an entry in the process table.

### 2. How does the program prevent zombies?
By using `signal(SIGCHLD, handler)`, the parent waits for the child’s exit and removes its entry.

### 3. What happens if `fork()` fails?
If `fork()` fails, the program prints an error message and does not create a child process.

