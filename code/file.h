#ifndef _FILE_MACRO_H_
#define _FILE_MACRO_H_

#include "URL.h"
#include "FTP_macros.h"
#include "socket.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int downloadFile(url *urlStruct);

int requestFile(int sockfd, char *ip, int port, char *path);

int saveFile(int dataSockfd, char *filename);

int getFileName(char *path, char *filename);

#endif
