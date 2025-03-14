
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "socket_service.h"
#include "command.h"
#include "util.h"

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/******************************************************************************
 * Function name:                   :Cli_ProcessCommand
 * Description:                     :Parses and processes user input commands.
 * Input parameter:                 :command (pointer to the user-input command string)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessCommand(sint8 *command)
{
    sint8 *cmd = strtok(command, " ");
    if (strncmp(cmd, "help", COMMAND_HELP_LEN) == 0)
    {
        Cli_ProcessHelp();
    }
    else if (strncmp(cmd, "myip", COMMAND_MYIP_LEN) == 0)
    {
        Cli_ProcessMyIp();
    }
    else if (strncmp(cmd, "myport", COMMAND_MYPORT_LEN) == 0)
    {
        Cli_ProcessMyPort();
    }
    else if (strncmp(cmd, "connect", COMMAND_CONNECT_LEN) == 0)
    {
        Cli_ProcessConnect();
    }
    else if (strncmp(cmd, "list", COMMAND_LIST_LEN) == 0)
    {
        Cli_ProcessList();
    }
    else if (strncmp(cmd, "terminate", COMMAND_TERMINATE_LEN) == 0)
    {
        Cli_ProcessTerminate();
    }
    else if (strncmp(cmd, "send", COMMAND_SEND_LEN) == 0)
    {
        Cli_ProcessSend();
    }
    else if (strncmp(cmd, "exit", COMMAND_EXIT_LEN) == 0)
    {
        Cli_ProcessExit();
    }
    else
    {
        printf("Invalid command\n");
        printf("%s", command);
    }
}

/******************************************************************************
 * Function name:                   :Cli_ProcessList
 * Description:                     :Displays a list of active socket connections.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessList(void)
{
    Util_PrintListSocket();
}

/******************************************************************************
 * Function name:                   :Cli_ProcessConnect
 * Description:                     :Establishes a connection to a remote peer.
 * Input parameter:                 :None (Extracts IP address and port from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessSend(void)
{
    sint32 SocketId;
    uint8 *Buffer;
    SocketList_InfoType *lpCurr = HeadSockList;

    /* Get IPaddr and TxBuffer */
    SocketId = atoi(strtok(NULL, " "));
    Buffer = strtok(NULL, "");

    /* Send to specific socket */
    while (lpCurr != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == SocketId)
        {
            if (E_OK == Safety_OverflowMessageSize(Buffer))
            {
                write(SocketId, Buffer, strlen(Buffer));
            }
            else
            {
                printf("[ERROR] Overflow message size\n");
            }

            return;
        }

        /* Move to next socket */
        lpCurr = lpCurr->next;
    }
}

/******************************************************************************
 * Function name:                   :Cli_ProcessConnect
 * Description:                     :Establishes a connection to a remote peer.
 * Input parameter:                 :None (Extracts IP address and port from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessConnect(void)
{
    sint32 Port;
    uint8 *IpAddr;

    /* Get IPaddr and TxBuffer */
    IpAddr = strtok(NULL, " ");
    Port = atoi(strtok(NULL, " "));

    /* Connect to specific port */
    Socket_ClientConnect(IpAddr, Port);
}

/******************************************************************************
 * Function name:                   :Cli_ProcessExit
 * Description:                     :Closes all active socket connections and terminates the program.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None (Calls `exit(0)`)
 *****************************************************************************/
void Cli_ProcessExit(void)
{
    SocketList_InfoType *lpCurr = HeadSockList;
    sint8 *message = strtok(NULL, "");

    while (lpCurr != NULL)
    {
        /* Close current socket connection */
        close(lpCurr->SocketInfo.Socket_fd);

        /* Move to next socket */
        lpCurr = lpCurr->next;
    }

    /* Remove all socket connection information */
    Socket_RemoveAllSocket();

    exit(0);
}

/******************************************************************************
 * Function name:                   :Cli_ProcessTerminate
 * Description:                     :Terminates a specific socket connection by ID.
 * Input parameter:                 :None (Extracts socket ID from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessTerminate(void)
{
    SocketList_InfoType *lpCurr = HeadSockList;
    uint32 socketId = atoi(strtok(NULL, " "));
    uint8 message[100];
    sprintf(message, "Port Number: %d", MyHostInfo.MyPort);

    /* Loop for specific socket connection */
    while (lpCurr != NULL)
    {
        if (lpCurr->SocketInfo.Socket_fd == socketId)
        {
            /* Remove connection */
            Socket_RemoveSocket(socketId);
            close(socketId);
            memset(message, 0, 100);
            sprintf(message, "Connection at port %d is removed", lpCurr->SocketInfo.Port);
            Util_PrintWrappedMessage(message);
            return;
        }

        /* Move to next socket */
        lpCurr = lpCurr->next;
    }
}

/******************************************************************************
 * Function name:                   :Cli_ProcessBoardcast
 * Description:                     :Sends a message to all active socket connections.
 * Input parameter:                 :None (Extracts message from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessBoardcast(void)
{
    SocketList_InfoType *lpCurr = HeadSockList;
    sint8 *message = strtok(NULL, "");

    while (lpCurr != NULL)
    {
        /* Send message to current socket */
        write(lpCurr->SocketInfo.Socket_fd, message, strlen(message));

        /* Move to next socket */
        lpCurr = lpCurr->next;
    }
}

/******************************************************************************
 * Function name:                   :Cli_ProcessMyPort
 * Description:                     :Displays the port number that the program is currently using.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessMyPort(void)
{
    uint8 message[100];
    sprintf(message, "Port Number: %d", MyHostInfo.MyPort);
    Util_PrintWrappedMessage(message);
}

/******************************************************************************
 * Function name:                   :Cli_ProcessMyIp
 * Description:                     :Displays the IP address of the host machine.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessMyIp(void)
{
    uint8 message[100];
    sprintf(message, "IP Address: %s", MyHostInfo.MyIp4Address);
    Util_PrintWrappedMessage(message);
}

/******************************************************************************
 * Function name:                   :Cli_ProcessHelp
 * Description:                     :Displays a help menu with available commands.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Cli_ProcessHelp(void)
{
    printf("\n+----------------------------------------------------------------------+\n");
    printf("| %-10s | %-55s |\n", "Command", "Description");
    printf("+------------+---------------------------------------------------------+\n");
    printf("| %-10s | %-55s |\n", "help", "Show available commands");
    printf("| %-10s | %-55s |\n", "myip", "Display the IP address of this machine");
    printf("| %-10s | %-55s |\n", "myport", "Show the port number this program is listening on");
    printf("| %-10s | %-55s |\n", "connect", "Connect to another peer (Usage: connect <IP> <port>)");
    printf("| %-10s | %-55s |\n", "list", "Display active connections");
    printf("| %-10s | %-55s |\n", "terminate", "Close a connection by ID (Usage: terminate <id>)");
    printf("| %-10s | %-55s |\n", "send", "Send message to a peer (Usage: send <id> <message>)");
    printf("| %-10s | %-55s |\n", "exit", "Close all connections and terminate the program");
    printf("+------------+---------------------------------------------------------+\n");
}
