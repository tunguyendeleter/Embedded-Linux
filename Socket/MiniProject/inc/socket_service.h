#ifndef INC_SOCKET_SERVICE_H
#define INC_SOCKET_SERVICE_H

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "std_type.h"
#include "safety.h"
#include "util.h"
#include <pthread.h>  

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define BUFFER_SIZE 100                     /* Maximum buffer size for messages */
#define BACKLOG 5                           /* Maximum number of pending client connections */
#define SOCKET_PING_MESSAGE "PING-SOCKET"   /* Message used for connection keep-alive */

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/******************************************************************************
 * Function name:                   :Socket_SendPrivate
 * Description:                     :Sends a private message to a specific client.
 * Input parameter:                 :TargetId (socket file descriptor of the target client)
 *                                  :MsgPtr (pointer to the message string to be sent)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_SendPrivate(sint32 TargetId, sint8 *MsgPtr);

/******************************************************************************
 * Function name:                   :Socket_ServerHandler
 * Description:                     :Handles communication with a connected client (server-side).
 * Input parameter:                 :arg (pointer to the socket file descriptor)
 * Output parameter:                :None
 * return:                          :NULL (thread function)
 *****************************************************************************/
extern void *Socket_ServerHandler(void *arg);

/******************************************************************************
 * Function name:                   :Socket_ClientHandler
 * Description:                     :Handles incoming messages from the server (client-side).
 * Input parameter:                 :arg (pointer to the socket file descriptor)
 * Output parameter:                :None
 * return:                          :NULL (thread function)
 *****************************************************************************/
extern void *Socket_ClientHandler(void *arg);

/******************************************************************************
 * Function name:                   :Socket_GetServerIpPort
 * Description:                     :Retrieves the server's IP address and port.
 * Input parameter:                 :sockfd (server socket file descriptor)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_GetServerIpPort(sint32 sockfd);

/******************************************************************************
 * Function name:                   :Socket_GetPeerIpPort
 * Description:                     :Retrieves the peer (client) IP address and port.
 * Input parameter:                 :sockfd (client socket file descriptor)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_GetPeerIpPort(sint32 sockfd);

/******************************************************************************
 * Function name:                   :Socket_UpdateMyHost
 * Description:                     :Updates the host's IP address and port.
 * Input parameter:                 :Ip4Address (pointer to a string containing the IPv4 address)
 *                                  :Port (port number to be assigned)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_UpdateMyHost(sint8 *Ip4Address, uint16 Port);

/******************************************************************************
 * Function name:                   :Socket_UpdateSocket
 * Description:                     :Updates the linked list of active sockets with a new client connection.
 * Input parameter:                 :Ip4Address (pointer to a string containing the client's IPv4 address)
 *                                  :Port (port number assigned to the client)
 *                                  :socket_fd (socket file descriptor for the client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_UpdateSocket(sint8 *Ip4Address, uint16 Port, sint32 socket_fd);

/******************************************************************************
 * Function name:                   :Socket_RemoveSocket
 * Description:                     :Removes a specific client socket from the linked list and closes it.
 * Input parameter:                 :socket_fd (socket file descriptor to be removed)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_RemoveSocket(sint32 socket_fd);

/******************************************************************************
 * Function name:                   :Socket_RemoveAllSocket
 * Description:                     :Removes and closes all active client sockets.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Socket_RemoveAllSocket(void);

/******************************************************************************
 * Function name:                   :Socket_ServerBind
 * Description:                     :Binds the server socket to a specified port.
 * Input parameter:                 :port (port number to bind the server to)
 * Output parameter:                :None
 * return:                          :E_OK (successful binding)
 *                                  :E_NOT_OK (binding failed)
 *****************************************************************************/
extern Std_ReturnType Socket_ServerBind(uint32 port);

/******************************************************************************
 * Function name:                   :Socket_ServerListen
 * Description:                     :Puts the server socket into listening mode, allowing it to accept connections.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :E_OK (successful)
 *                                  :E_NOT_OK (listening failed)
 *****************************************************************************/
extern Std_ReturnType Socket_ServerListen(void);

/******************************************************************************
 * Function name:                   :Socket_ServerAccept
 * Description:                     :Accepts incoming client connections and assigns them to handler threads.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :E_OK (success)
 *                                  :E_NOT_OK (failure)
 *****************************************************************************/
extern Std_ReturnType Socket_ServerAccept(void);

/******************************************************************************
 * Function name:                   :Socket_ClientConnect
 * Description:                     :Establishes a client connection to a specified server.
 * Input parameter:                 :ip (pointer to a string containing the server's IPv4 address)
 *                                  :port (port number to connect to)
 * Output parameter:                :None
 * return:                          :E_OK (successful connection)
 *                                  :E_NOT_OK (connection failed)
 *****************************************************************************/
extern Std_ReturnType Socket_ClientConnect(sint8 *ip, sint32 port);

/******************************************************************************
 * Function name:                   :Socket_GetSocket
 * Description:                     :Retrieves the socket information from the linked list based on the socket ID.
 * Input parameter:                 :socketId (socket file descriptor to search for)
 * Output parameter:                :None
 * return:                          :Pointer to `SocketList_InfoType` if found, NULL otherwise.
 *****************************************************************************/
extern SocketList_InfoType *Socket_GetSocket(sint32 socketId);

/******************************************************************************
 * Function name:                   :Socket_CheckPingMessage
 * Description:                     :Checks if a received message is a "PING" message used for connection keep-alive.
 * Input parameter:                 :Message (pointer to the received message)
 * Output parameter:                :None
 * return:                          :E_OK (message is a valid "PING")
 *                                  :E_NOT_OK (message is not a "PING")
 *****************************************************************************/
extern Std_ReturnType Socket_CheckPingMessage(sint8 *Message);


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/
/******************************************************************************
 * Variable name:                   :Socket_HostSocketfd
 * Description:                     :Temporary storage for a host socket ID.
 *****************************************************************************/
extern sint32 Socket_HostSocketfd;

/******************************************************************************
 * Variable name:                   :lock
 * Description:                     :Mutex lock for thread-safe access to the socket list.
 *****************************************************************************/
extern pthread_mutex_t lock;

/******************************************************************************
 * Variable name:                   :CurrSockList
 * Description:                     :Pointer to the currently active client in the linked list.
 *****************************************************************************/
extern SocketList_InfoType *CurrSockList;

/******************************************************************************
 * Variable name:                   :HeadSockList
 * Description:                     :Pointer to the first client in the linked list.
 *****************************************************************************/
extern SocketList_InfoType *HeadSockList;

/******************************************************************************
 * Variable name:                   :MyHostInfo
 * Description:                     :Stores the server's IP address and port.
 *****************************************************************************/
extern HostConfig_InfoType MyHostInfo;

#endif /* INC_SOCKET_SERVICE_H */
