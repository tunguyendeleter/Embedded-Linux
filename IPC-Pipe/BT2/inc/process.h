#ifndef INC_PROCESS_H
#define INC_PROCESS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/wait.h>

typedef struct Process
{
    /* Process ID */
    pid_t pid;
    char is_child;

    /* Methods */
    void (*start)(struct Process *self, void (*process_handler)(int *, int *));
    void (*wait)(struct Process *self);
} Process;

extern int pipe_fd1[2], pipe_fd2[2];

Process create_process();
void start_process(Process *self, void (*process_handler)(int *, int *));
void stop_process(Process *self);
void Process_InitPipe(int *pipe_fd1, int *pipe_fd2);
void Process_One(int *pipe_fd1, int *pipe_fd2);
void Process_Two(int *pipe_fd1, int *pipe_fd2);
void Process_Three(int *pipe_fd1, int *pipe_fd2);

#endif /* INC_PROCESS_H */