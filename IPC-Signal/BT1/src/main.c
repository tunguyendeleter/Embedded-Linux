#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#define MAX_SIGINT      3

int sigint_count = 0;

void SIGINT_handler(int num)
{
    sigint_count++;
    printf("\n[INFO] SIGINT received: %d\n", sigint_count);
}

int main()
{
    /* Register SIGINT signal handler */
    if (signal(SIGINT, SIGINT_handler) < 0)
    {
        printf("\n[ERROR] Register signal fail");
        return 0;
    }
    
    /* Break loop after 3 SIGINT received */
    while (sigint_count < MAX_SIGINT)
    {
        /* Do nothing */
    }

    return 0;
}