#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#define MAX_SEND 5

int sigusr1_count = 0;
pid_t child_pid = 0;

void SIGALRM_handler(int num)
{
    sigusr1_count++;
    printf("[PARENT] PID = %d, Sending SIGUSR1 to [CHILD]\n", getpid());
    kill(child_pid, SIGUSR1);
    /* Restart alarm */
    if (sigusr1_count < MAX_SEND)
    {
        alarm(2);
    }
    /* End child process after MAX_SEND times */
    else
    {
        kill(child_pid, SIGKILL);   
    }
}

void SIGUSR1_handler(int num)
{
    printf("[CHILD] PID = %d, Received SIGUSR1 from [PARENT]\n", getpid());
}

int main()
{
    pid_t child;
    child = fork();
    if (child > 0)
    {
        /* This is PARENT lifespan */
        printf("[PARENT] Im parent, PID = %d\n", getpid());

        /* Register SIGALRM signal */
        if (signal(SIGALRM, SIGALRM_handler) == SIG_ERR)
        {
            perror("\n[ERROR] Register SIGALRM failed");
            exit(EXIT_FAILURE);
        }
        child_pid = child;
        alarm(2);
    }
    else if (child == 0)
    {
        /* This is CHILD lifespan */
        printf("[CHILD] Im child, PID = %d\n", getpid());

        /* Register SIGUSR1 signal */
        if (signal(SIGUSR1, SIGUSR1_handler) == SIG_ERR)
        {
            perror("\n[ERROR] Register SIGUSR1 failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Fork failed */
        perror("[ERROR] Fork failed");
        exit(EXIT_FAILURE);
    }

    while (sigusr1_count < MAX_SEND)
    {
        /* Do nothing*/
    }
    if (child > 0)
    {
        printf("[PARENT] I have finished sending...");
        wait(NULL); /* Wait exit status to prevent child process to become zombie */
    }

    return 0;
}