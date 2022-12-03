#ifndef _SOCKET_DEFINES_H_
#define _SOCKET_DEFINES_H_

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include "FTP_macros.h"

typedef struct {
    char ip[20]; // TO USE IN PASSIVE
    char response[2048];
    int code;
} sockResponse;

typedef struct {
    char command[5];
    char argument[2048];
} sockCommand;

int openConnection(const char *host, int port);

int getIpFromHost(const char *host, char *ip);

int readResponse(int sockFd, sockResponse * response);

int sendCommand(int sockFd, sockCommand * command);

int login(int sockFd, char *user, char *password);

#endif
