#ifndef INC_SAFETY_H
#define INC_SAFETY_H

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "std_type.h"
#include "socket_service.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define MIN_PORT 1          /* Minimum valid port number */
#define MAX_PORT 65535      /* Maximum valid port number */
#define NUM_OCTET 4         /* Expected number of octets in a valid IPv4 address */

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/******************************************************************************
 * Function name:                   :Safety_CheckInvalidPort
 * Description:                     :Checks if a given port number is within the valid range.
 * Input parameter:                 :port (port number to be validated)
 * Output parameter:                :None
 * return:                          :E_OK (valid port number)
 *                                  :E_NOT_OK (invalid port number)
 *****************************************************************************/
Std_ReturnType Safety_CheckInvalidPort(uint32 port);

/******************************************************************************
 * Function name:                   :Safety_CheckInvalidIp
 * Description:                     :Validates an IPv4 address.
 * Input parameter:                 :ip (pointer to a string containing the IP address)
 * Output parameter:                :None
 * return:                          :E_OK (valid IP address)
 *                                  :E_NOT_OK (invalid IP address)
 *****************************************************************************/
Std_ReturnType Safety_CheckInvalidIp(const sint8 *ip);

/******************************************************************************
 * Function name:                   :Safety_OverflowMessageSize
 * Description:                     :Checks if the size of a message exceeds the maximum allowed buffer size.
 * Input parameter:                 :message (pointer to the message string)
 * Output parameter:                :None
 * return:                          :E_OK (valid message size)
 *                                  :E_NOT_OK (message exceeds allowed size)
 *****************************************************************************/
Std_ReturnType Safety_OverflowMessageSize(uint8 *message);

#endif /* INC_SAFETY_H */
