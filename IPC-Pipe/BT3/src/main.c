#include "process.h"

int main()
{    
    /* Open pipe */
    int pipe_fd[2];
    Process_InitPipe(pipe_fd);

    /* Create child process */
    Process proc = create_process();
    proc.start(&proc, Process_Parent, Process_Child);
    proc.stop(&proc);    

    return 0;
}
