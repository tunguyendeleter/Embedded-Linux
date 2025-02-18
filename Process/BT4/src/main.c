#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t child1, child2;
    child1 = fork();

    if (child1 == 0)
    {
        printf("[CHILD 1] I'm the child, my PID = %d\n", getpid());
        sleep(1);  // sleep to prevent zomebie process
        exit(111); // Exit with 111 status
    }
    else if (child1 < 0)
    {
        perror("[ERROR] Fork failed");
    }

    child2 = fork();
    if (child2 == 0)
    {
        printf("[CHILD 2] I'm the child, my PID = %d\n", getpid());
        sleep(2);  // sleep to prevent zomebie process
        exit(222); // Exit with 222 status
    }
    else if (child2 < 0)
    {
        perror("[ERROR] Fork failed");
    }

    if (child2 > 0 && child1 > 0)
    {
        pid_t pid1, pid2;
        int status1, status2;
        printf("[PARENT] I'm the parent, my PID = %d\n", getpid());
        pid1 = wait(&status1);
        printf("[PARENT] Receive child1's status:\n");
        printf("[PARENT] PID child1 = %d\n", pid1);
        printf("[PARENT] WIFEXITED(child1) = %d, WEXITSTATUS(child1) = %d\n", WIFEXITED(status1), WEXITSTATUS(status1));

        pid2 = wait(&status2);
        printf("[PARENT] Receive child2's status:\n");
        printf("[PARENT] PID child2 = %d\n", pid2);
        printf("[PARENT] WIFEXITED(child2) = %d, WEXITSTATUS(child2) = %d\n", WIFEXITED(status2), WEXITSTATUS(status2));
        exit(0); // Exit with 0 status
    }

    return 0;
}
