#ifndef INC_UTIL_H
#define INC_UTIL_H

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "socket_service.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define TABLE_WIDTH 72                   /* Total table width for formatted message display */
#define MAX_LINE_WIDTH (TABLE_WIDTH - 4) /* Usable width inside table, accounting for padding */

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/******************************************************************************
 * Function name:                   :Util_PrintWrappedMessage
 * Description:                     :Prints a message inside a formatted box, wrapping text if it exceeds
 *                                    the maximum line width.
 * Input parameter:                 :message (pointer to the message string to be printed)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintWrappedMessage(uint8 *message);

/******************************************************************************
 * Function name:                   :Util_PrintAnnouceReceiveMessage
 * Description:                     :Displays an announcement when a message is received from a client.
 * Input parameter:                 :sock_fd (socket file descriptor of the client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintAnnouceReceiveMessage(sint32 sock_fd);

/******************************************************************************
 * Function name:                   :Util_PrintAnnouceConnectMessage
 * Description:                     :Displays an announcement when a new client connection is established.
 * Input parameter:                 :sock_fd (socket file descriptor of the connected client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintAnnouceConnectMessage(sint32 sock_fd);

/******************************************************************************
 * Function name:                   :Util_PrintAnnouceDisconnectMessage
 * Description:                     :Displays an announcement when a client disconnects from the server.
 * Input parameter:                 :sock_fd (socket file descriptor of the disconnected client)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintAnnouceDisconnectMessage(sint32 sock_fd);

/******************************************************************************
 * Function name:                   :Util_PrintListSocket
 * Description:                     :Displays a formatted table listing all active socket connections,
 *                                    including socket ID, port, and IP address.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Util_PrintListSocket(void);

#endif /* INC_UTIL_H */
