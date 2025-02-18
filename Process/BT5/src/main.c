#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
This function create a child only for execlp(), parent process will remain alive
*/
void kill_handler(int pid, int signal)
{
    pid_t child = fork();
    if (child == 0)
    {
        char PID[10];
        char signum[5];
        sprintf(PID, "%d", pid);
        sprintf(signum, "-%d", signal);
        execlp("kill", "kill", signum, PID, NULL);
    }
}

/*
This function create a child only for execvp(), parent process will remain alive
*/
void ps_handler(int num_pid, int *pid)
{
    pid_t child = fork();
    if (child == 0)
    {
        char *arg[10] = {"ps", "-f", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
        char PID[10][10]; // Allocate memory for PID strings

        for (int i = 0; i < num_pid; i++)
        {
            sprintf(PID[i], "%d", pid[i]); // Store PID as string
            arg[i + 2] = PID[i];           // Assign to argument list
        }
        execvp(arg[0], arg);
    }
}

/*
The main function will be the GRAND PARENT
We will fork a PARENT from GRAND PARENT
We will fork an orphan child and a zombie child from PARENT
*/
int main()
{
    printf("[GRAND PARENT] Im the grand parent, PID = %d\n", getpid());
    pid_t parent, orphan, zombie;

    /* Fork the PARENT from GRAND PARENT */
    parent = fork();

    if (parent > 0)
    {
        /* This is GRAND PARENT lifespan */
        printf("[GRAND PARENT] I will go to sleep... 3 seconds\n");
        sleep(3);
    }
    else if (parent == 0)
    {
        /* Fork the CHILD_1 from PARENT */
        zombie = fork();
        if (zombie > 0)
        {
            /* Fork the CHILD_2 from PARENT */
            orphan = fork();
            if (orphan > 0)
            {
                /* This is PARENT lifespan */
                printf("[PARENT] Im the parent, PID = %d\n", getpid());
                sleep(1);
                printf("[PARENT] Im will kill mychild [CHILD_1] => [CHILD_1] becomes a zombie\n");
                kill_handler((int)zombie, 9);
                printf("[PARENT] Im will kill myself [PARENT] => [CHILD_2] becomes an orphan\n");
                kill_handler(getpid(), 9);
                while (1) /* Stop PARENT in this loop */
                    ;
            }
            else if (orphan == 0)
            {
                /* This is CHILD_2 lifespan */
                printf("[CHILD_2] Im the 2nd child, PID = %d\n", getpid());
                while (1) /* Stop CHILD_2 in this loop */
                    ;
            }
            else
            {
                perror("[ERROR] Fork CHILD_2 failed");
            }
        }
        else if (zombie == 0)
        {
            /* This is CHILD_1 lifespan */
            printf("[CHILD_1] Im the 1st child, PID = %d\n", getpid());
            while (1) /* Stop CHILD_1 in this loop */
                ;
        }
        else
        {
            perror("[ERROR] Fork CHILD_1 failed");
        }
    }
    else
    {
        perror("[ERROR] Fork PARENT failed");
    }

    /* This is GRAND PARENT lifespan */
    printf("[GRAND PARENT] Im woken up...\n");
    printf("[GRAND PARENT] Check our family status: ps -f %d %d %d %d\n", getpid(), parent, parent + 1, parent + 2);
    int pid_list[4] = {getpid(), parent, parent + 1, parent + 2};
    ps_handler(4, pid_list);
    while (1) /* Stop GRAND PARENT in this loop */
        ;
    return 0;
}
