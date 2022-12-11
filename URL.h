#ifndef _URL_DEFINES_H_
#define _URL_DEFINES_H_


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <regex.h>


typedef struct {
    char user[256];
    char password[256];
    char host[512];
    char path[512];
} url;


int parseURL(const char *urlString, url *urlStruct);


#endif
