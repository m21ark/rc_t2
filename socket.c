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
            if (response->code == ENTERING_PASSIVE_MODE) {
                int p1, p2, p3, p4, p5, p6;
                sscanf(buf,"227 Entering Passive Mode (%d,%d,%d,%d,%d,%d[^ .)\n]", &p1, &p2, &p3, &p4, &p5, &p6);
                sprintf(response->ip, "%d.%d.%d.%d", p1, p2, p3, p4);
                response->port = p5 * 256 + p6;
            }
			break;
		}
    }
    printf("%s", response->response);
    return totalBytesRead;
}


int sendCommand(int sockFd, sockCommand * command) {
    FILE * socket = fdopen(sockFd, "w");

    char buf[1024];
    strcpy(buf, command->command);
    strcat(buf, " ");
    strcat(buf, command->argument);
    strcat(buf, CRLF);

    int bytes = write(sockFd, buf, strlen(buf));
    if (bytes != strlen(buf)) {
        perror("write()");
        return -1;
    }
    
    printf("Sent: %s", buf);

    return bytes;
}

int login(int sockFd, char *user, char *password) {

    // SEND USER COMMAND
    sockCommand cmd = {USER, ""};
    strcpy(cmd.argument, user);

    if (sendCommand(sockFd, &cmd) < 0)
    {
        perror("Error sending USER cmd");
        return -1;
    }

    // ./download ftp://anonymous:pass@ftp.up.pt/pub/kodi/timestamp.txt
    sockResponse sockRes;
    readResponse(sockFd, &sockRes);
    
    if (!(sockRes.code == USERNAME_OK_GIVE_PASSWORD || sockRes.code == LOGIN_SUCCESSFUL))
    {
        perror("Please specify a valid Username");
        return -1;
    }

    //SEND PASS COMMAND

    strcpy(cmd.command, PASS);
    strcpy(cmd.argument, password);

    if (sendCommand(sockFd, &cmd) < 0)
    {
        perror("Error sending PASS cmd");
        return -1;
    }
    
    readResponse(sockFd, &sockRes);

    if (sockRes.code != LOGIN_SUCCESSFUL)
    {
        perror("Please specify a valid Username");
        return -1;
    }
        

    return 0;
}

int passiveMode(int sockFd, sockResponse * response) {

    sockCommand cmd = {PASV, ""};

    if (sendCommand(sockFd, &cmd) < 0)
    {
        perror("Error sending PASSIVE cmd");
        return -1;
    }


    readResponse(sockFd, response);
    
    if (response->code != ENTERING_PASSIVE_MODE)
    {
        perror("Error entering PASSIVE mode");
        return -1;
    }
    
    return 0;
}

