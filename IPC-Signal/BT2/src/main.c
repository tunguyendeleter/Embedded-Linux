#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define MAX_TIME 10
int second = 0;

void SIGALRM_handler(int num)
{
    /* Restart alarm for 1 second */
    second++;
    printf("[INFO] Timer: %d seconds\n", second);
    alarm(1);
}

int main()
{
    /* Start alarm for 1 second */
    alarm(1);
    printf("[INFO] Timer started!...\n");

    /* Register SIGALRM signal handler */
    if (signal(SIGALRM, SIGALRM_handler) < 0)
    {
        printf("\n[ERROR] Register signal fail");
        return 0;
    }

    /* Break loop after 10 second */
    while (second < MAX_TIME)
    {
        /* Do nothing */
    }
    printf("[INFO] Timer finished!...\n");

    return 0;
}