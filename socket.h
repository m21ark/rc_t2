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


typedef struct {
    char ip[20]; // TO USE IN PASSIVE
    char response[2048];
    int code;
} sockResponse;

int openConnection(const char *host, const char *port);

int getIpFromHost(const char *host, char *ip);

int readResponse(int sockFd, sockResponse * response); 

#endif
