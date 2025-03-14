
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "safety.h"

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
Std_ReturnType Safety_CheckInvalidPort(uint32 port)
{
    Std_ReturnType Retval = E_OK;

    /* Check if port is used by host */
    if (MyHostInfo.MyPort == port)
    {
        Retval = E_NOT_OK;
    }

    /* Check invalid port range */
    if (E_NOT_OK != Retval)
    {
        if (port < MIN_PORT && port > MAX_PORT)
        {
            Retval = E_NOT_OK;
        }
    }

    return Retval;
}

/******************************************************************************
 * Function name:                   :Safety_CheckInvalidIp
 * Description:                     :Validates an IPv4 address.
 * Input parameter:                 :ip (pointer to a string containing the IP address)
 * Output parameter:                :None
 * return:                          :E_OK (valid IP address)
 *                                  :E_NOT_OK (invalid IP address)
 *****************************************************************************/
Std_ReturnType Safety_CheckInvalidIp(const sint8 *ip)
{
    Std_ReturnType Retval = E_OK;

    if (NULL == ip)
    {
        Retval = E_NOT_OK; /* Null input is invalid */
    }

    if (E_NOT_OK != Retval)
    {
        /* Make a copy of ip since strtok() modifies the original string */
        uint8 ipCopy[16]; /* Maximum IPv4 length "255.255.255.255" + null terminator */
        strncpy(ipCopy, ip, sizeof(ipCopy));
        ipCopy[sizeof(ipCopy) - 1] = '\0'; /* Ensure null termination */

        uint8 *token;
        uint8 OctetCount = 0;

        token = strtok(ipCopy, "."); /* First token */
        while (token != NULL && Retval == E_OK)
        {
            /* Check if token contains only digits */
            for (uint8 i = 0; token[i] != '\0'; i++)
            {
                if (token[i] < '0' && token[i] > '9')
                {
                    Retval = E_NOT_OK; /* Invalid character found */
                    break;
                }
            }

            /* Convert token to integer and validate range */
            if (E_NOT_OK != Retval)
            {
                int checkOctet = atoi(token);
                if (checkOctet < 0 || checkOctet > 255)
                {
                    Retval = E_NOT_OK; /* Out of valid IP range */
                }
            }

            OctetCount++;
            token = strtok(NULL, "."); /* Get next token */
        }

        /* A valid IPv4 must have exactly 4 octets */
        if (OctetCount != NUM_OCTET)
        {
            Retval = E_NOT_OK;
        }
    }

    return Retval;
}

/******************************************************************************
 * Function name:                   :Safety_OverflowMessageSize
 * Description:                     :Checks if the size of a message exceeds the maximum allowed buffer size.
 * Input parameter:                 :message (pointer to the message string)
 * Output parameter:                :None
 * return:                          :E_OK (valid message size)
 *                                  :E_NOT_OK (message exceeds allowed size)
 *****************************************************************************/
Std_ReturnType Safety_OverflowMessageSize(uint8 *message)
{
    Std_ReturnType Retval = E_OK;

    /* Null input is invalid */
    if (message == NULL)
    {
        Retval = E_NOT_OK;
    }

    /* Check size is valid */
    if (E_NOT_OK != Retval)
    {
        uint32 len = strlen(message);

        if (len > BUFFER_SIZE)
        {
            Retval = E_NOT_OK;
        }
    }
    return Retval;
}
