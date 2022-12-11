#ifndef _FTP_MACROS_H_
#define _FTP_MACROS_H_

//CMDS
#define USER "USER"
#define PASS "PASS"
#define PASV "PASV"
#define RETR "RETR"
#define QUIT "QUIT"

//RESPONSES
#define  SERVICE_READY_FOR_NEW_USER 220
#define  USERNAME_OK_GIVE_PASSWORD 331
#define  LOGIN_SUCCESSFUL 230
#define  LOGIN_ERROR_IN   530
#define  ENTERING_PASSIVE_MODE 227
#define  FILE_OK_RETR_READY         150 
#define  TRANSFER_COMPLETE   226 

// terminator
#define CRLF "\r\n" 

#endif
