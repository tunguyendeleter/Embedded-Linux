#include "util.h"

/******************************************************************************
 * Function name:                   :Util_PrintWrappedMessage
 * Description:                     :Prints a message inside a formatted box, wrapping text if it exceeds
 *                                    the maximum line width.
 * Input parameter:                 :message (pointer to the message string to be printed)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintWrappedMessage(uint8 *message)
{
    int len = strlen(message);
    int start = 0;

    printf("+----------------------------------------------------------------------+\n");
    while (start < len)
    {
        printf("| %-*.*s |\n", MAX_LINE_WIDTH, MAX_LINE_WIDTH, message + start);
        start += MAX_LINE_WIDTH;
    }
    printf("+----------------------------------------------------------------------+\n");
}

/******************************************************************************
 * Function name:                   :Util_PrintAnnouceReceiveMessage
 * Description:                     :Displays an announcement when a message is received from a client.
 * Input parameter:                 :sock_fd (socket file descriptor of the client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintAnnouceReceiveMessage(sint32 sock_fd)
{
    uint8 message[100];
    int len = strlen(message);
    int start = 0;
    bool isFound = E_NOT_OK;

    if (HeadSockList == NULL_PTR)
    {
        return;
    }
    SocketList_InfoType *lpCurr = HeadSockList;
    while (lpCurr != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == sock_fd)
        {
            sprintf(message, "Receive message from %s:%d", lpCurr->SocketInfo.Ip4Address, lpCurr->SocketInfo.Port);
            isFound = E_OK;
        }
        lpCurr = lpCurr->next;
    }

    if (isFound == E_OK)
    {
        printf("\n+----------------------------------------------------------------------+\n");
        while (start < len)
        {
            printf("| %-*.*s |\n", MAX_LINE_WIDTH, MAX_LINE_WIDTH, message + start);
            start += MAX_LINE_WIDTH;
        }
        printf("+----------------------------------------------------------------------+\n");
    }
}

/******************************************************************************
 * Function name:                   :Util_PrintAnnouceConnectMessage
 * Description:                     :Displays an announcement when a new client connection is established.
 * Input parameter:                 :sock_fd (socket file descriptor of the connected client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintAnnouceConnectMessage(sint32 sock_fd)
{
    uint8 messageA[100];
    uint8 messageB[100];
    int len;
    int start;
    bool isFound = E_NOT_OK;

    if (HeadSockList == NULL_PTR)
    {
        return;
    }
    SocketList_InfoType *lpCurr = HeadSockList;
    while (lpCurr != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == sock_fd)
        {
            sprintf(messageA, "A new connection is established ");
            sprintf(messageB, "ID : %-2d | Port : %-6d | IP : %-16s", sock_fd, lpCurr->SocketInfo.Port, lpCurr->SocketInfo.Ip4Address);
            isFound = E_OK;
        }
        lpCurr = lpCurr->next;
    }

    if (isFound == E_OK)
    {
        len = strlen(messageA);
        start = 0;
        printf("\n+----------------------------------------------------------------------+\n");
        while (start < len)
        {
            printf("| %-*.*s |\n", MAX_LINE_WIDTH, MAX_LINE_WIDTH, messageA + start);
            start += MAX_LINE_WIDTH;
        }
        printf("+----------------------------------------------------------------------+\n");
        len = strlen(messageB);
        start = 0;
        while (start < len)
        {
            printf("| %-*.*s |\n", MAX_LINE_WIDTH, MAX_LINE_WIDTH, messageB + start);
            start += MAX_LINE_WIDTH;
        }
        printf("+----------------------------------------------------------------------+\n");
    }
}

/******************************************************************************
 * Function name:                   :Util_PrintAnnouceDisconnectMessage
 * Description:                     :Displays an announcement when a client disconnects from the server.
 * Input parameter:                 :sock_fd (socket file descriptor of the disconnected client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintAnnouceDisconnectMessage(sint32 sock_fd)
{
    uint8 message[100];
    int start = 0;
    int len;
    bool isFound = E_NOT_OK;

    if (HeadSockList == NULL_PTR)
    {
        return;
    }
    SocketList_InfoType *lpCurr = HeadSockList;
    while (lpCurr != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == sock_fd)
        {
            sprintf(message, "A new peer at port %d has disconnected", lpCurr->SocketInfo.Port);
            isFound = E_OK;
        }
        lpCurr = lpCurr->next;
    }

    if (isFound == E_OK)
    {
        len = strlen(message);
        start = 0;
        printf("\n+----------------------------------------------------------------------+\n");
        while (start < len)
        {
            printf("| %-*.*s |\n", MAX_LINE_WIDTH, MAX_LINE_WIDTH, message + start);
            start += MAX_LINE_WIDTH;
        }
        printf("+----------------------------------------------------------------------+\n");
    }
}

/******************************************************************************
 * Function name:                   :Util_PrintListSocket
 * Description:                     :Displays a formatted table listing all active socket connections,
 *                                    including socket ID, port, and IP address.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintListSocket(void)
{
    uint8 message[100];
    int len;
    int start;
    SocketList_InfoType *lpCurr = HeadSockList;

    if (lpCurr == NULL_PTR)
    {
        return;
    }

    memset(message, 0, 100);
    sprintf(message, "ID        | Port        | IP        ");
    Util_PrintWrappedMessage(message);

    while (lpCurr != NULL_PTR)
    {
        start = 0;
        memset(message, 0, 100);
        sprintf(message, "%-2d        | %-6d      | %-16s     ", lpCurr->SocketInfo.Socket_fd, lpCurr->SocketInfo.Port, lpCurr->SocketInfo.Ip4Address);
        len = strlen(message);
        while (start < len)
        {
            printf("| %-*.*s |\n", MAX_LINE_WIDTH, MAX_LINE_WIDTH, message + start);
            start += MAX_LINE_WIDTH;
        }
        lpCurr = lpCurr->next;
    }

    printf("+----------------------------------------------------------------------+\n");
}