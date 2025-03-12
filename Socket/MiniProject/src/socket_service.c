#include "socket_service.h"

/* Global Variables */
/******************************************************************************
 * Variable name:                   :Socket_HostSocketfd
 * Description:                     :Temporary storage for a host socket ID.
 *****************************************************************************/
sint32 Socket_HostSocketfd;

/******************************************************************************
 * Variable name:                   :lock
 * Description:                     :Mutex lock for thread-safe access to the socket list.
 *****************************************************************************/
pthread_mutex_t lock;

/******************************************************************************
 * Variable name:                   :CurrSockList
 * Description:                     :Pointer to the currently active client in the linked list.
 *****************************************************************************/
SocketList_InfoType *CurrSockList = NULL_PTR;

/******************************************************************************
 * Variable name:                   :HeadSockList
 * Description:                     :Pointer to the first client in the linked list.
 *****************************************************************************/
SocketList_InfoType *HeadSockList = NULL_PTR;

/******************************************************************************
 * Variable name:                   :MyHostInfo
 * Description:                     :Stores the server's IP address and port.
 *****************************************************************************/
HostConfig_InfoType MyHostInfo;

/******************************************************************************
 * Function name:                   :Socket_SendPrivate
 * Description:                     :Function to send a private message to a specific client
 * Input parameter:                 :TargetId (socket file descriptor of the target client)
 *                                  :MsgPtr (pointer to the message string to be sent)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_SendPrivate(sint32 TargetId, sint8 *MsgPtr)
{
    SocketList_InfoType *lpCurr = HeadSockList;

    pthread_mutex_lock(&lock); /* Lock the mutex to safely access client list */
    while (lpCurr != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == TargetId)
        {                                                                /* Find the target client */
            write(lpCurr->SocketInfo.Socket_fd, MsgPtr, strlen(MsgPtr)); /* Send message */
            break;
        }
        lpCurr = lpCurr->next; /* Move to next client */
    }
    pthread_mutex_unlock(&lock); /* Unlock the mutex */
}

/******************************************************************************
 * Function name:                   :Socket_GetSocket
 * Description:                     :Retrieves the socket information from the linked list based on the socket ID.
 * Input parameter:                 :socketId (socket file descriptor to search for)
 * Output parameter:                :None
 * return:                          :Pointer to `SocketList_InfoType` if found, NULL otherwise.
 *****************************************************************************/
SocketList_InfoType *Socket_GetSocket(sint32 socketId)
{
    SocketList_InfoType *lpCurr = HeadSockList;

    while (lpCurr != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == socketId)
        { /* Find the target client */
            return lpCurr;
        }
        lpCurr = lpCurr->next; /* Move to next client */
    }
    return NULL_PTR;
}

/******************************************************************************
 * Function name:                   :Socket_ClientHandler
 * Description:                     :Function to handle individual client communication
 * Input parameter:                 :arg (pointer to the socket file descriptor)
 * Output parameter:                :None
 * return:                          :NULL (thread function)
 *****************************************************************************/
void *Socket_ClientHandler(void *arg)
{
    sint32 server_socket = *(sint32 *)arg; /* Extract socket descriptor */
    free(arg);                             /* Free dynamically allocated memory */

    sint8 buffer[BUFFER_SIZE];
    fd_set read_fds;

    /* Get socket information from specific sockeId */
    SocketList_InfoType *lpSocketInfo = Socket_GetSocket(server_socket);

    /* Annouce a new connection socket */
    Util_PrintAnnouceConnectMessage(server_socket);

    while (1)
    {
        /* Check if message is received from the server */
        memset(buffer, 0, BUFFER_SIZE);
        sint32 bytes_received = recv(server_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0)
        {
            Util_PrintAnnouceDisconnectMessage(server_socket);
            Socket_RemoveSocket(server_socket);
            break;
        }
        buffer[bytes_received - 1] = '\0'; /* Remove newline char */

        /* Check if this is not ping message from server then receive this message */
        if (E_NOT_OK == Socket_CheckPingMessage(buffer))
        {
            uint8 message[200]; /* Create formated message */
            sprintf(message, "Client: %s", buffer);
            Util_PrintAnnouceReceiveMessage(server_socket);
            Util_PrintWrappedMessage(message);
        }
    }

    close(server_socket);
    return NULL;
}

/******************************************************************************
 * Function name:                   :Socket_ServerHandler
 * Description:                     :Function to handle individual socket communication
 * Input parameter:                 :arg (pointer to the socket file descriptor)
 * Output parameter:                :None
 * return:                          :NULL (thread function)
 *****************************************************************************/
void *Socket_ServerHandler(void *arg)
{
    sint32 client_socket = *(sint32 *)arg; /* Extract socket descriptor */
    free(arg);                             /* Free dynamically allocated memory */

    sint8 buffer[BUFFER_SIZE];
    fd_set read_fds;
    struct timeval timeout;

    /* Get socket information */
    SocketList_InfoType *lpSocketInfo = Socket_GetSocket(client_socket);

    /* Announce new connection */
    Util_PrintAnnouceConnectMessage(client_socket);

    while (1)
    {
        /* Set timeout for select() to check for disconnection */
        timeout.tv_sec = 1; /* Check every 5 seconds */
        timeout.tv_usec = 0;

        FD_ZERO(&read_fds);
        FD_SET(client_socket, &read_fds);

        int activity = select(client_socket + 1, &read_fds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            perror("[ERROR] Select error");
            break;
        }

        if (activity > 0)
        {
            /* Check if message is received from the client */
            memset(buffer, 0, BUFFER_SIZE);
            sint32 bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0)
            {
                /* Client disconnected */
                Util_PrintAnnouceDisconnectMessage(client_socket);
                Socket_RemoveSocket(client_socket);
                break;
            }

            buffer[bytes_received] = '\0'; /* Null-terminate received message */
            printf("Received from client: %s\n", buffer);
        }
        else
        {
            /* No data received, send a heartbeat message */
            if (send(client_socket, SOCKET_PING_MESSAGE, sizeof(SOCKET_PING_MESSAGE), 0) == -1)
            {
                perror("[ERROR] Client disconnected (send failed)");
                Util_PrintAnnouceDisconnectMessage(client_socket);
                Socket_RemoveSocket(client_socket);
                break;
            }
        }
    }

    close(client_socket);
    return NULL;
}

/******************************************************************************
 * Function name:                   :Socket_RemoveSocket
 * Description:                     :Removes a specific client socket from the linked list and closes it.
 * Input parameter:                 :socket_fd (socket file descriptor to be removed)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_RemoveSocket(sint32 socket_fd)
{
    pthread_mutex_lock(&lock); /* Lock the mutex for thread safety */

    /* Check if list is empty */
    if (HeadSockList == NULL_PTR)
    {
        pthread_mutex_unlock(&lock);
        return;
    }

    /* Remove if first socket of the list */
    SocketList_InfoType *lpCurr = HeadSockList;

    if (lpCurr->SocketInfo.Socket_fd == socket_fd)
    {
        HeadSockList = lpCurr->next;
        if (HeadSockList != NULL_PTR) /* Only update if there is a next node */
            HeadSockList->prev = NULL_PTR;

        close(lpCurr->SocketInfo.Socket_fd); /* Close the socket before removing */
        free(lpCurr);
        pthread_mutex_unlock(&lock);
        return;
    }

    /* Traverse to find the socket in the middle */
    while (lpCurr != NULL_PTR && lpCurr->next != NULL_PTR)
    {
        if (lpCurr->SocketInfo.Socket_fd == socket_fd)
        {
            lpCurr->prev->next = lpCurr->next;
            lpCurr->next->prev = lpCurr->prev;
            close(lpCurr->SocketInfo.Socket_fd); /* Close the socket before removing */
            free(lpCurr);
            pthread_mutex_unlock(&lock);
            return;
        }

        lpCurr = lpCurr->next;
    }

    /* If last socket is found, remove it */
    if (lpCurr->SocketInfo.Socket_fd == socket_fd)
    {
        CurrSockList = lpCurr->prev;
        CurrSockList->next = NULL;
        close(lpCurr->SocketInfo.Socket_fd); /* Close the socket */
        free(lpCurr);
    }

    pthread_mutex_unlock(&lock); /* Unlock the mutex */
}

/******************************************************************************
 * Function name:                   :Socket_UpdateMyHost
 * Description:                     :Function to update the host config
 * Input parameter:                 :Ip4Address (pointer to a string containing the IPv4 address)
 *                                  :Port (port number to be assigned)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_UpdateMyHost(sint8 *Ip4Address, uint16 Port)
{
    strncpy(MyHostInfo.MyIp4Address, Ip4Address, INET_ADDRSTRLEN);
    MyHostInfo.MyPort = Port;
}

/******************************************************************************
 * Function name:                   :Socket_UpdateSocket
 * Description:                     :Function to update the linked list with a new client
 * Input parameter:                 :Ip4Address (pointer to a string containing the client's IPv4 address)
 *                                  :Port (port number assigned to the client)
 *                                  :socket_fd (socket file descriptor for the client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_UpdateSocket(sint8 *Ip4Address, uint16 Port, sint32 socket_fd)
{
    pthread_mutex_lock(&lock); /* Lock the mutex for thread safety */

    /* Create new socket info for the client */
    SocketList_InfoType *NewSocket = (SocketList_InfoType *)malloc(sizeof(SocketList_InfoType));
    if (!NewSocket)
    {
        perror("Memory allocation failed");
        pthread_mutex_unlock(&lock);
        return;
    }

    /* Assign client details */
    strncpy(NewSocket->SocketInfo.Ip4Address, Ip4Address, INET_ADDRSTRLEN);
    NewSocket->SocketInfo.Port = Port;
    NewSocket->SocketInfo.Socket_fd = socket_fd;
    NewSocket->next = NULL_PTR;

    /* Add the new client to the linked list */
    if (HeadSockList == NULL_PTR)
    {
        HeadSockList = NewSocket;
        CurrSockList = HeadSockList;
    }
    else
    {
        CurrSockList->next = NewSocket;
        NewSocket->prev = CurrSockList;
        CurrSockList = NewSocket;
    }

    pthread_mutex_unlock(&lock); /* Unlock the mutex */
}

/******************************************************************************
 * Function name:                   :Socket_ServerBind
 * Description:                     :Function to bind the server to a port
 * Input parameter:                 :port (port number to bind the server to)
 * Output parameter:                :None
 * return:                          :E_OK (successful binding)
 *                                  :E_NOT_OK (binding failed)
 *****************************************************************************/
Std_ReturnType Socket_ServerBind(uint32 port)
{
    Std_ReturnType Retval = E_OK;
    struct sockaddr_in Server_Info;

    /* Check invalid port number */
    if (E_NOT_OK == Safety_CheckInvalidPort(port))
    {
        Retval = E_NOT_OK;
    }

    if (Retval != E_NOT_OK)
    {
        /* Create a TCP socket */
        Socket_HostSocketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (Socket_HostSocketfd == -1)
        {
            printf("[ERROR] Create socket fail\n");
            Retval = E_NOT_OK;
        }
        /* Configure server address */
        Server_Info.sin_family = AF_INET;
        Server_Info.sin_addr.s_addr = INADDR_ANY; /* Listen on all network interfaces */
        Server_Info.sin_port = htons(port);

        if (Retval != E_NOT_OK)
        {
            /* Bind the server socket */
            if (bind(Socket_HostSocketfd, (struct sockaddr *)&Server_Info, sizeof(Server_Info)) == -1)
            {
                printf("[ERROR] Bind socket fail\n");
                Retval = E_NOT_OK;
            }
        }

        if (Retval != E_NOT_OK)
        {
            printf("[INFO] Bind socket success\n");

            /* Update host ip and port */
            Socket_GetServerIpPort(Socket_HostSocketfd);
        }
    }

    return Retval;
}

/******************************************************************************
 * Function name:                   :Socket_ServerListen
 * Description:                     :Function to put the server in listening mode
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :E_OK (successful)
 *                                  :E_NOT_OK (listening failed)
 *****************************************************************************/
Std_ReturnType Socket_ServerListen(void)
{
    Std_ReturnType Retval = E_OK;

    /* Start listening for incoming connections */
    if (listen(Socket_HostSocketfd, BACKLOG) == -1)
    {
        printf("[ERROR] Listen socket fail\n");
        Retval = E_NOT_OK;
    }
    else
    {
        printf("[INFO] Listen socket success\n");
    }

    return Retval;
}

/******************************************************************************
 * Function name:                   :Socket_ServerAccept
 * Description:                     :Function to accept incoming client connections
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :E_OK (success)
 *                                  :E_NOT_OK (failure)
 *****************************************************************************/
Std_ReturnType Socket_ServerAccept(void)
{
    Std_ReturnType Retval = E_OK;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    sint32 *client_fd;

    /* Server loop to accept multiple clients */
    while (1) /* Keep accepting new connections */
    {
        /* Allocate memory for socket descriptor */
        client_fd = malloc(sizeof(int));
        if (!client_fd)
        {
            perror("[ERROR] Memory allocation failed");
            continue;
        }

        /* Wait for any connection request from client */
        *client_fd = accept(Socket_HostSocketfd, (struct sockaddr *)&client_addr, &client_len);
        if (*client_fd == -1)
        {
            perror("[ERROR] Accept socket fail");
            free(client_fd);
            continue;
        }

        /* Get client IP and port */
        sint8 client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

        /* Add client to linked list */
        Socket_UpdateSocket(client_ip, ntohs(client_addr.sin_port), *client_fd);

        /* Create a thread to handle this client */
        pthread_t thread;
        if (pthread_create(&thread, NULL, Socket_ServerHandler, client_fd) != 0)
        {
            perror("[ERROR] Failed to create client handler thread");
            close(*client_fd);
            free(client_fd);
            continue;
        }

        pthread_detach(thread); /* Allow thread to clean up itself after exiting */
    }

    return Retval;
}

/******************************************************************************
 * Function name:                   :Socket_GetServerIpPort
 * Description:                     :Retrieves the server's IP address and port.
 * Input parameter:                 :sockfd (server socket file descriptor)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_GetServerIpPort(sint32 sockfd)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    sint8 server_ip[INET_ADDRSTRLEN];

    /* Get the server's IP from the bound socket */
    if (getsockname(sockfd, (struct sockaddr *)&addr, &addr_len) == -1)
    {
        perror("getsockname failed");
        return;
    }

    /* Convert binary IP to string */
    inet_ntop(AF_INET, &addr.sin_addr, server_ip, INET_ADDRSTRLEN);

    /* Update to host information */
    Socket_UpdateMyHost(server_ip, ntohs(addr.sin_port));
}

/******************************************************************************
 * Function name:                   :Socket_GetPeerIpPort
 * Description:                     :Retrieves the peer (client) IP address and port.
 * Input parameter:                 :sockfd (client socket file descriptor)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_GetPeerIpPort(sint32 sockfd)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    sint8 server_ip[INET_ADDRSTRLEN];

    /* Get the server's address from the connected socket */
    if (getpeername(sockfd, (struct sockaddr *)&addr, &addr_len) == -1)
    {
        perror("getpeername failed");
        return;
    }

    /* Convert binary IP to human-readable format */
    inet_ntop(AF_INET, &addr.sin_addr, server_ip, INET_ADDRSTRLEN);
    printf("Connected to Server IP: %s, Port: %d\n", server_ip, ntohs(addr.sin_port));

    /* Add client to linked list */
    Socket_UpdateSocket(server_ip, ntohs(addr.sin_port), sockfd);
}

/******************************************************************************
 * Function name:                   :Socket_ClientConnect
 * Description:                     :Establishes a client connection to a specified server.
 * Input parameter:                 :ip (pointer to a string containing the server's IPv4 address)
 *                                  :port (port number to connect to)
 * Output parameter:                :None
 * return:                          :E_OK (successful connection)
 *                                  :E_NOT_OK (connection failed)
 *****************************************************************************/
Std_ReturnType Socket_ClientConnect(sint8 *ip, sint32 port)
{
    /* Allocate memory for socket descriptor */
    sint32 *sockfd = malloc(sizeof(int));
    struct sockaddr_in Server_Info;
    if (!sockfd)
    {
        perror("Memory allocation failed");
        return E_NOT_OK;
    }
    printf("Connecting to IP = %s, Port = %d\n", ip, port);

    /* Create socket */
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1)
    {
        perror("Socket creation failed");
        free(sockfd);
        return E_NOT_OK;
    }

    /* Configure server address */
    Server_Info.sin_family = AF_INET;
    Server_Info.sin_port = htons(port);

    /* Convert IP address */
    if (inet_pton(AF_INET, ip, &Server_Info.sin_addr) <= 0)
    {
        perror("Invalid address");
        close(*sockfd);
        free(sockfd);
        return E_NOT_OK;
    }

    /* Connect to the server */
    if (connect(*sockfd, (struct sockaddr *)&Server_Info, sizeof(Server_Info)) < 0)
    {
        perror("Connection failed");
        close(*sockfd);
        free(sockfd);
        return E_NOT_OK;
    }

    printf("Connected successfully to %s:%d\n", ip, port);

    /* Get port and ip the actual server IP */
    Socket_GetPeerIpPort(*sockfd);

    /* Create a thread to handle this client */
    pthread_t thread;
    if (pthread_create(&thread, NULL, Socket_ClientHandler, sockfd) != 0)
    {
        perror("Failed to create client handler thread");
        close(*sockfd);
        free(sockfd);
        return E_NOT_OK;
    }

    pthread_detach(thread);
    return E_OK;
}

/******************************************************************************
 * Function name:                   :Socket_RemoveAllSocket
 * Description:                     :Removes and closes all active client sockets.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Socket_RemoveAllSocket(void)
{
    pthread_mutex_lock(&lock); /* Lock the mutex for thread safety */

    /* First socket of the list */
    SocketList_InfoType *lpCurr = HeadSockList;

    /* Remove the list */
    while (lpCurr != NULL_PTR)
    {
        /* Free memory of socket from list */
        lpCurr = lpCurr->next;
        free(HeadSockList);
        HeadSockList = lpCurr;
    }

    CurrSockList = HeadSockList;

    pthread_mutex_unlock(&lock); /* Unlock the mutex */
}

/******************************************************************************
 * Function name:                   :Socket_CheckPingMessage
 * Description:                     :Checks if a received message is a "PING" message used for connection keep-alive.
 * Input parameter:                 :Message (pointer to the received message)
 * Output parameter:                :None
 * return:                          :E_OK (message is a valid "PING")
 *                                  :E_NOT_OK (message is not a "PING")
 *****************************************************************************/
Std_ReturnType Socket_CheckPingMessage(sint8 *Message)
{
    Std_ReturnType Retval = E_NOT_OK;
    if (strncmp(SOCKET_PING_MESSAGE, Message, strlen(Message)) == 0)
    {
        Retval = E_OK;
    }
    return Retval;
}