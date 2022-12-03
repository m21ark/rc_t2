#include "file.h"


int downloadFile(url * urlStruct) {
    int sockfd;

    // Open a connection to the server, 21 -> command port
    if ((sockfd = openConnection(urlStruct->host, 21)) == -1) {
        perror("socket");
        return -1;
    }
    

    

}


