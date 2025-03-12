#ifndef INC_STD_TYPE_H
#define INC_STD_TYPE_H

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/******************************************************************************
 * Typedef name:                    : uint8
 * Description:                      : Defines an 8-bit unsigned integer.
 *****************************************************************************/
typedef unsigned char uint8;

/******************************************************************************
 * Typedef name:                    : uint16
 * Description:                      : Defines a 16-bit unsigned integer.
 *****************************************************************************/
typedef unsigned short uint16;

/******************************************************************************
 * Typedef name:                    : uint32
 * Description:                      : Defines a 32-bit unsigned integer.
 *****************************************************************************/
typedef unsigned int uint32;

/******************************************************************************
 * Typedef name:                    : sint8
 * Description:                      : Defines an 8-bit signed integer.
 *****************************************************************************/
typedef signed char sint8;

/******************************************************************************
 * Typedef name:                    : sint16
 * Description:                      : Defines a 16-bit signed integer.
 *****************************************************************************/
typedef signed short sint16;

/******************************************************************************
 * Typedef name:                    : sint32
 * Description:                      : Defines a 32-bit signed integer.
 *****************************************************************************/
typedef signed int sint32;

/******************************************************************************
 * Typedef name:                    : bool
 * Description:                      : Defines a boolean type as an unsigned 8-bit integer.
 *                                      0 (false), 1 (true).
 *****************************************************************************/
typedef unsigned char bool;

/* === Standard Return Type Definition === */
/******************************************************************************
 * Typedef name:                    : Std_ReturnType
 * Description:                      : Defines a standard return type using `sint8` for function success/failure.
 *****************************************************************************/
typedef sint8 Std_ReturnType;

/* === Standard Return Values === */
/******************************************************************************
 * Macro name:                       : E_OK
 * Description:                       : Standard return value indicating success (0).
 *****************************************************************************/
#define E_OK (Std_ReturnType)0

/******************************************************************************
 * Macro name:                       : E_NOT_OK
 * Description:                       : Standard return value indicating failure (1).
 *****************************************************************************/
#define E_NOT_OK (Std_ReturnType)1

/******************************************************************************
 * Macro name:                       : NULL_PTR
 * Description:                       : Defines a null pointer constant for pointer initialization.
 *****************************************************************************/
#define NULL_PTR ((void *)0)

/* === Host Configuration Structure === */
/******************************************************************************
 * Structure name:                   : HostConfig_InfoType
 * Description:                       : Stores the host's IP address and port number.
 *****************************************************************************/
typedef struct host
{
    sint8 MyIp4Address[INET_ADDRSTRLEN]; /* IPv4 address of the host */
    uint16 MyPort;                       /* Port number assigned to the host */
} HostConfig_InfoType;

/* === Socket Information Structure === */
/******************************************************************************
 * Structure name:                   : Socket_InfoType
 * Description:                       : Stores information about a socket connection.
 *****************************************************************************/
typedef struct sock
{
    sint8 Ip4Address[INET_ADDRSTRLEN]; /* IPv4 address of the remote client/server */
    uint16 Port;                       /* Port number of the connection */
    sint32 Socket_fd;                  /* Socket file descriptor */
} Socket_InfoType;

/* === Linked List Structure for Active Sockets === */
/******************************************************************************
 * Structure name:                   : SocketList_InfoType
 * Description:                       : Maintains a linked list of active socket connections.
 *****************************************************************************/
typedef struct socklist
{
    Socket_InfoType SocketInfo; /* Socket information */
    struct socklist *next;      /* Pointer to the next socket in the list */
    struct socklist *prev;      /* Pointer to the previous socket in the list */
} SocketList_InfoType;

#endif /* INC_STD_TYPE_H */
