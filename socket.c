#include "socket.h"

int openConnection(const char *host, const char *port) {

    int sockfd;
    struct sockaddr_in server_addr;

    /*server address handling*/

    char ip[33];

    getIpFromHost(host, ip);

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(port);        /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }
    /*connect to the server*/
    if (connect(sockfd,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect()");
        return -1;
    }

    return sockfd;
}

int getIpFromHost(const char *host, char *ip)
{
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        return -1;
    }

    *ip = inet_ntoa(*((struct in_addr *) h->h_addr));
    return 0;
}

