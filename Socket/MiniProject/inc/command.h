#ifndef INC_COMMAND_H
#define INC_COMMAND_H

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "std_type.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define COMMAND_HELP_LEN            4U   /* Length of "help" command */
#define COMMAND_MYIP_LEN            4U   /* Length of "myip" command */
#define COMMAND_MYPORT_LEN          6U   /* Length of "myport" command */
#define COMMAND_CONNECT_LEN         7U   /* Length of "connect" command */
#define COMMAND_LIST_LEN            4U   /* Length of "list" command */
#define COMMAND_TERMINATE_LEN       9U   /* Length of "terminate" command */
#define COMMAND_SEND_LEN            4U   /* Length of "send" command */
#define COMMAND_EXIT_LEN            4U   /* Length of "exit" command */

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
extern void Cli_ProcessCommand(sint8 *command);

/******************************************************************************
 * Function name:                   :Cli_ProcessList
 * Description:                     :Displays a list of active socket connections.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessList(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessSend
 * Description:                     :Sends a message to a specific client by socket ID.
 * Input parameter:                 :None (Extracts socket ID and message from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessSend(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessConnect
 * Description:                     :Establishes a connection to a remote peer.
 * Input parameter:                 :None (Extracts IP address and port from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessConnect(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessExit
 * Description:                     :Closes all active socket connections and terminates the program.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None (Calls `exit(0)`)
 *****************************************************************************/
extern void Cli_ProcessExit(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessTerminate
 * Description:                     :Terminates a specific socket connection by ID.
 * Input parameter:                 :None (Extracts socket ID from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessTerminate(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessBoardcast
 * Description:                     :Sends a message to all active socket connections.
 * Input parameter:                 :None (Extracts message from user input)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessBoardcast(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessMyPort
 * Description:                     :Displays the port number that the program is currently using.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessMyPort(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessMyIp
 * Description:                     :Displays the IP address of the host machine.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessMyIp(void);

/******************************************************************************
 * Function name:                   :Cli_ProcessHelp
 * Description:                     :Displays a help menu with available commands.
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
extern void Cli_ProcessHelp(void);

/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/

#endif /* INC_COMMAND_H */
