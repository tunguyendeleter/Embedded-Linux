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
    void (*start)(struct Process *self, void (*parent_handler)(int *), void (*child_handler)(int *));
    void (*stop)(struct Process *self);
} Process;

void start_process(Process *self, void (*parent_handler)(int *), void (*child_handler)(int *));
void stop_process(Process *self);
void Process_InitPipe(int *pipe_fd);
void Process_Parent(int *pipe_fd);
void Process_Child(int *pipe_fd);
Process create_process();

#endif /* INC_PROCESS_H */