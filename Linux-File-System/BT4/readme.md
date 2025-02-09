# README: File Metadata Information Tool

## Overview
This program retrieves and displays metadata information of a specified file using the `stat` system call in Linux. It provides details such as file type, size, and timestamps related to access, modification, and status change.

## Features
- Reads metadata of a specified file.
- Identifies the file type (regular file, directory, symbolic link, etc.).
- Displays file size in bytes.
- Logs the last status change, last access time, and last modification time.

## Project Structure
```
.
├── bin
│   ├── file_stat
│   └── text.txt
├── inc
├── lib
├── Makefile
├── obj
│   └── main.o
├── readme.md
└── src
    └── main.c
```

## Compilation
To compile the program, use the following command:

```sh
make all
```
or
```sh
gcc -o file_stat file_stat.c
```

## Usage
Run the program by providing the filename as an argument:

```sh
./file_stat <filename>
```

For example:

```sh
./file_stat example.txt
```

## Output
The program outputs metadata details for the specified file:

```
[INFO] Reading stat file ./text.txt
[INFO] File type:     regular file
[INFO] File name:     ./text.txt
[INFO] File size:       18
[INFO] Last status change:      Sun Feb  9 07:46:46 2025
[INFO] Last file access:        Sun Feb  9 07:46:46 2025
[INFO] Last file modification:  Sun Feb  9 07:46:46 2025
```

## Code Explanation
1. **Argument Check**: The program verifies that exactly one argument (filename) is provided.
2. **Retrieve File Metadata**: Uses `lstat()` to get information about the file.
3. **Error Handling**: If `lstat()` fails, an error message is displayed.
4. **File Type Identification**: Uses bitwise operations on `st_mode` to determine file type.
5. **Display Metadata**: Prints the filename, size, and timestamps for last status change, access, and modification.

## Notes
- The program uses `lstat()` instead of `stat()` to ensure it correctly retrieves metadata for symbolic links.
- File size is displayed in bytes.
- Timestamps are formatted using `ctime()` for readability.

## License
This project is open-source and free to use under the MIT License.

