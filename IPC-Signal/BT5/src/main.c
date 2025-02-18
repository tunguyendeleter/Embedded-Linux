#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

#define IS_STRING_EQUA(str1, str2) (strcmp(str1, str2) == 0)

void SIGINT_handler(int signum)
{
    printf("[INFO] SIGINT received\n");
}

int main()
{
    fd_set readfds;
    char buffer[100];

    /* Register SIGINT signal handler */
    if (signal(SIGINT, SIGINT_handler) == SIG_ERR)
    {
        perror("[ERROR] Failed to catch SIGINT");
        exit(EXIT_FAILURE);
    }

    /* Pulling input from keyboard */
    while (1)
    {
        FD_ZERO(&readfds);              // Clear the set
        FD_SET(STDIN_FILENO, &readfds); // Add stdin (keyboard) to the set

        /* Use select() to get input stdin data */
        printf("Enter: ");
        fflush(stdout); // Ensure prompt is displayed immediately
        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL);

        /* Check error select fail */
        if (ret == -1)
        {
            /* Do nothing in case: Ctrl + C */
        }
        /* Check data */
        else if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strlen(buffer) - 1] = '\0';

            /* If input is SIGINT then catch the signal */
            if (IS_STRING_EQUA(buffer, "SIGINT"))
            {
                kill(getpid(), SIGINT);
            }
            /* If input is SIGTERM then terminate the process */
            else if (IS_STRING_EQUA(buffer, "SIGTERM"))
            {
                kill(getpid(), SIGTERM);
            }
        }
    }

    return 0;
}
