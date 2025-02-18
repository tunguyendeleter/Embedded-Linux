#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void SIGCHLD_handler(int signum)
{
    printf("[PARENT] Wait child to exit...\n");
    wait(NULL);
}

int main()
{
    pid_t p = fork();
    if (p >= 0)
    {
        if (p > 0)
        {
            /* Wait to prevent child process to become zombie */
            if (signal(SIGCHLD, SIGCHLD_handler) == SIG_ERR)
            {
                perror("\n[ERROR] Register SIGCHLD failed");
                exit(EXIT_FAILURE);
            }

            printf("[INFO] Hello world! I'm the parent, my child's PID = %d\n", p);
            sleep(2);
        }
        else
        {
            printf("[INFO] Hello world! I'm the child, my PID = %d\n", getpid());
            sleep(1);
            exit(0); // Exit with 0 status
        }
    }
    else
    {
        perror("[ERROR] Fork failed");
    }
    return 0;
}
