#include "process.h"

/* Function to create pipe */
void Process_InitPipe(int *pipe_fd)
{
    /* Create a pipe */
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe() failed");
        exit(1);
    }
}

/* Function to handle parent task */
void Process_Parent(int *pipe_fd)
{
    char *filename = "./text.txt";
    char ReadBuffer[1000];

    /* Open text.txt file */
    int file_fd = open(filename, O_RDWR, 0666);
    if (file_fd == -1)
    {
        printf("[ERROR] Error opening file\n");
    }
    else
    {
        printf("[INFO] Open file: %s\n", filename);

        /* Read data from file */
        memset(ReadBuffer, 0, sizeof(ReadBuffer)); /* Clear bufffer */
        read(file_fd, ReadBuffer, sizeof(ReadBuffer));

        /* Close unused read end */
        close(pipe_fd[0]);

        /* Write data to child process */
        write(pipe_fd[1], ReadBuffer, sizeof(ReadBuffer));
        printf("[PARENT] sending...\n");

        /* Close write end after writing */
        close(pipe_fd[1]);

        /* Close file after read */
        close(file_fd);
    }
}

/* Function to handle child task */
void Process_Child(int *pipe_fd)
{
    char ReadBuffer[1000];

    /* Close unused write end */
    close(pipe_fd[1]);

    /* Read data from file */
    read(pipe_fd[0], ReadBuffer, sizeof(ReadBuffer));
    printf("[CHILD] receive...\n");

    /* Print number of characters */
    int size = strlen(ReadBuffer);
    printf("Number of characters in message: %d", size);

    /* Close read end after writing */
    close(pipe_fd[0]);
}

/* Function to start the process */
void start_process(Process *self, void (*parent_handler)(int *), void (*child_handler)(int *))
{
    /* Open pipe */
    int pipe_fd[2];
    Process_InitPipe(pipe_fd);

    self->pid = fork();

    if (self->pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (self->pid == 0)
    { /* Child process */
        self->is_child = 1;
        if (child_handler)
        {
            child_handler(pipe_fd);
        }
    }
    else
    { /* Parent process */
        self->is_child = 0;
        if (parent_handler)
        {
            parent_handler(pipe_fd);
        }
    }
}

/* Function to stop the process (only applicable for parent) */
void stop_process(Process *self)
{
    if (!self->is_child && self->pid > 0)
    {
        wait(NULL);
    }
}

/* Constructor for the Process struct */
Process create_process()
{
    Process proc;
    proc.pid = -1;
    proc.is_child = 0;
    proc.start = start_process;
    proc.stop = stop_process;
    return proc;
}