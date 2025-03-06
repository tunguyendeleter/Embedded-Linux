#include "process.h"

int pipe_fd1[2], pipe_fd2[2];

int main()
{
    /* Initialize IPC-pipe */
    Process_InitPipe(pipe_fd1, pipe_fd2);

    /* Initialize process 1 */
    Process proc1 = create_process();
    proc1.start(&proc1, Process_One);

    /* Initialize process 2 */
    Process proc2 = create_process();
    proc2.start(&proc2, Process_Two);

    /* Initialize process 3 */
    Process proc3 = create_process();
    proc3.start(&proc3, Process_Three);

    /* Close child process after all */
    proc1.wait(&proc1);
    proc2.wait(&proc2);
    proc3.wait(&proc3);

    return 0;
}
