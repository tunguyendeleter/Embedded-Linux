#include "process.h"

extern int pipe_fd1[2], pipe_fd2[2];

int find_match(const char *text, const char *replace, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (text[i] != replace[i])
            return 0; // Mismatch found
    }
    return 1; // Full match found
}

void add_space_string(char *buffer, int space)
{
    int len = strlen(buffer);
    for (int i = len; i >= 0; i--)
    {
        buffer[i + space] = buffer[i];
    }
    while (space)
    {
        buffer[space--] = '-';
    }
}

void replace_string(char *buffer, char *text, char *replace)
{
    int len = strlen(buffer);
    int buffer_idx = 0;
    if (strlen(text) > strlen(replace))
    {
        return;
    }
    
    while (len--)
    {
        if (find_match(buffer, text, strlen(text)))
        {
            add_space_string(buffer, strlen(replace) - strlen(text));
            memcpy(buffer, replace, strlen(replace));
            buffer += sizeof(text);
        }
        else
        {
            buffer++;
        }
    }
}

void Process_InitPipe(int *pipe_fd1, int *pipe_fd2)
{
    /* Create a pipe */
    if (pipe(pipe_fd1) == -1)
    {
        perror("Pipe() failed");
        exit(1);
    }
    /* Create a pipe */
    if (pipe(pipe_fd2) == -1)
    {
        perror("Pipe() failed");
        exit(1);
    }
}

void Process_One(int *pipe_fd1, int *pipe_fd2)
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
        /* Read data from file */
        memset(ReadBuffer, 0, sizeof(ReadBuffer)); /* Clear bufffer */
        printf("[PROCESS 1] Open file: %s\n", filename);
        read(file_fd, ReadBuffer, sizeof(ReadBuffer));

        /* Close unused read end */
        close(pipe_fd1[0]);
        close(pipe_fd2[0]);
        close(pipe_fd2[1]);

        /* Write data to process 2 */
        write(pipe_fd1[1], ReadBuffer, sizeof(ReadBuffer));
        printf("[PROCESS 1] Sending to [PROCESS 2]... \n");

        /* Close write end after writing */
        close(pipe_fd1[1]);

        /* Close file after read */
        close(file_fd);
    }
}

void Process_Two(int *pipe_fd1, int *pipe_fd2)
{
    char ReadBuffer[1000];

    /* Close unused write end */
    close(pipe_fd1[1]);
    close(pipe_fd2[0]);

    /* Read data from file */
    printf("[PROCESS 2] receive... \n");
    read(pipe_fd1[0], ReadBuffer, sizeof(ReadBuffer));

    /* Change data */
    // replace_string(ReadBuffer, "Anh", "Ta");
    // replace_string(ReadBuffer, "anh", "ta");
    replace_string(ReadBuffer, "Em", "Nàng");
    replace_string(ReadBuffer, "em", "nàng");
    replace_string(ReadBuffer, "ánh mắt", "đôi mắt");

    /* Write data to process 3 */
    printf("[PROCESS 2] Sending to [PROCESS 3]... \n");
    write(pipe_fd2[1], ReadBuffer, sizeof(ReadBuffer));

    /* Close read end after writing */
    close(pipe_fd1[0]);
    close(pipe_fd2[1]);
}

void Process_Three(int *pipe_fd1, int *pipe_fd2)
{
    char ReadBuffer[1000];

    /* Close unused write end */
    close(pipe_fd1[0]);
    close(pipe_fd1[1]);
    close(pipe_fd2[1]);

    /* Read data from file */
    read(pipe_fd2[0], ReadBuffer, sizeof(ReadBuffer));
    printf("[PROCESS 3] receive...: WTF a love letter\n%s\n", ReadBuffer);

    /* Close read end after writing */
    close(pipe_fd2[0]);
}

/* Function to start the process */
void start_process(Process *self, void (*process_handler)(int *, int *))
{
    /* Create child process */
    self->pid = fork();

    /* Perform child process handler */
    if (self->pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (self->pid == 0)
    {
        self->is_child = 1;
        process_handler(pipe_fd1, pipe_fd2);
        exit(0);
    }
}

/* Function to wait the process (only applicable for parent) */
void wait_process(Process *self)
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
    proc.wait = wait_process;
    return proc;
}