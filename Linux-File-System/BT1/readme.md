# README: O\_APPEND File Write Test

## Problem Statement

Write a program that:

- Opens a file with the `O_APPEND` flag.
- Moves the file pointer to the beginning using `lseek()`.
- Writes data to the file.
- Repeats the process twice to observe the behavior of `O_APPEND`.

## Expected Behavior

Regardless of calling `lseek(fd, 0, SEEK_SET)`, the `O_APPEND` flag forces all writes to occur at the **end of the file**. This means that:

- The first write appends "1st write" to the file.
- The second write appends "2nd write" after the first write.

The file content will be:

```
1st write2nd write
```

Instead of writing at the start of the file, the new data is always appended to the end.

## Code Compilation

```sh
make all
```
or
```sh
gcc -o main ./src/main.c
```

## Running the Program

```sh
./bin/main
```

## Directory Structure

```
.
├── bin
│   ├── main
│   └── test.txt
├── inc
├── lib
├── Makefile
├── obj
│   └── main.o
└── src
    └── main.c
```

## Explanation

1. The program opens `test.txt` with `O_APPEND`.
2. It calls `lseek(fd, 0, SEEK_SET)`, but due to `O_APPEND`, writing still happens at the end.
3. The process repeats, appending data instead of overwriting.

## Conclusion

File test.txt được open với cờ O_APPEND, và dùng lseek(fd, 0, SEEK_SET) để di chuyển con trỏ về đầu file, nhưng khi write thì data vẫn được lưu ở cuối file, bởi vì cờ O_APPEND cho phép system ưu tiên việc di chuyển con trỏ về đầu file mỗi khi write dữ liệu vào file

