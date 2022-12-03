#include "socket.h"

int openConnection(const char *host, int port) {

    int sockfd;
    struct sockaddr_in server_addr;

    /*server address handling*/

    char ip[33];

    getIpFromHost(host, ip);

    printf("IP: %s\n", ip);

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

inline int getIpFromHost(const char *host, char *ip)
{
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        return -1;
    }

    char * tmp;
    tmp = inet_ntoa(*((struct in_addr *) h->h_addr));
    strcpy(ip, tmp);
    printf("\nIP: %s", ip);

    return 0;
}


int readResponse(int sockFd, sockResponse * response) {
    FILE * socket = fdopen(sockFd, "r");

    char * buf;
    size_t bytesRead = 0;
	int totalBytesRead = 0;

	while (getline(&buf, &bytesRead, socket) > 0) {
		strncat(response->response, buf, bytesRead - 1);
		totalBytesRead += bytesRead;

		if (buf[3] == ' ') {
			sscanf(buf, "%d", &response->code);
			break;
		}
    }

    return totalBytesRead;
}


int sendCommand(int sockFd, sockCommand * command) {
    FILE * socket = fdopen(sockFd, "w");

    char buf[1024];
    strcpy(buf, command->command);
    strcat(buf, " ");
    strcat(buf, command->argument);

    int bytes = write(sockFd, buf, strlen(buf));
    if (bytes != strlen(buf)) {
        perror("write()");
        return -1;
    }
    
    printf("Sent: %s\n", buf);

    return bytes;
}
