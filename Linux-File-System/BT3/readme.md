# File Operations Program

## Overview
This C program performs file operations such as creating, reading, and writing based on user input. The program takes command-line arguments to determine the file name, operation mode, and data size.

## Directory Structure
```
.
├── bin        # Contains the compiled executable and created files
│   ├── filename.txt  # Example file created by the program
│   └── main         # Executable file
├── inc        # (Empty, can be used for header files)
├── lib        # (Empty, can be used for libraries)
├── Makefile   # Build automation script
├── obj        # Contains compiled object files
│   └── main.o # Object file for main.c
└── src        # Contains source files
    └── main.c # The main program source code
```

## Compilation
To compile the program, use:
```sh
make all
```
This will generate the executable `bin/main`.

## Usage
Run the program with the following command-line arguments:
```sh
./bin/main <filename> <size> <operation> <data>
```
- `<filename>`: The name of the file (without extension).
- `<size>`: The number of bytes to read or write.
- `<operation>`: `r` for read, `w` for write.
- `<data>`: The data to write (only required for write operation).

### Examples
#### Writing to a file:
```sh
./bin/main myfile 5 w hello
```
Creates `myfile.txt` and writes "hello" into it.

#### Reading from a file:
```sh
./bin/main myfile 5 r
```
Reads 5 bytes from `myfile.txt` and displays them.

## Error Handling
- If more than 5 arguments are passed, the program prints an error message.
- If the file cannot be created, an error message is displayed.
- If an invalid operation (`r/w`) is provided, the program prints an error message.

## Dependencies
- Standard C libraries: `stdio.h`, `sys/stat.h`, `sys/file.h`, `unistd.h`, `string.h`, `stdlib.h`

## Notes
- The program reads or writes the specified number of bytes but does not handle file offsets or appending.
- The file is created with read/write permissions (`0666`).

