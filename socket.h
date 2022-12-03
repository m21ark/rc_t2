#ifndef _SOCKET_DEFINES_H_
#define _SOCKET_DEFINES_H_

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int openConnection(const char *host, const char *port);

int getIpFromHost(const char *host, char *ip);


#endif
