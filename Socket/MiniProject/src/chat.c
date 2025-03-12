
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "socket_service.h"
#include "command.h"
#include "safety.h"

/******************************************************************************
 * Function name:                   :ServerThread
 * Description:                     :This function handle all server activities
 * Input parameter:                 :arg (port number)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void *ServerThread(void *arg) {
    int port = *((int *)arg);
    free(arg);  // Free dynamically allocated memory

    /* Start the server */
    Socket_ServerBind(port);
    Socket_ServerListen();
    Socket_ServerAccept();
    return NULL;
}

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);

    /* Initialize mutex */
    pthread_mutex_init(&lock, NULL);

    /* Show the help menu */
    Cli_ProcessHelp();

    /* Start the server in a separate thread */
    pthread_t server_thread;
    int *server_port = malloc(sizeof(int));
    *server_port = port;
    pthread_create(&server_thread, NULL, ServerThread, server_port);
    pthread_detach(server_thread);  // Detach thread to avoid memory leaks

    /* Command input loop */
    while (1) {
        sleep(1);
        char command[BUFFER_SIZE];
        printf("Enter command: ");
        fgets(command, BUFFER_SIZE, stdin);
        Cli_ProcessCommand(command);
    }

    /* Cleanup */
    pthread_mutex_destroy(&lock);
    return 0;
}
