#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("[ERROR] Invalid command-line argument\n");
        return 0;
    }

    if (strcmp(argv[1], "1") == 0)
    {
        printf("[INFO] Call child process to run ls by execlp()\n");
        execlp("ls", "ls", "-l", NULL);
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        char *arg[] = {"date", NULL};
        printf("[INFO] Call child process to run date by execvp()\n");
        execvp(arg[0], arg);
    }
    else
    {
        printf("[ERROR] Invalid command-line argument\n");
    }

    return 0;
}
