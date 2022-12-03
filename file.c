#include "file.h"


int downloadFile(url * urlStruct) {
    int sockfd;

    // Open a connection to the server, 21 -> command port
    if ((sockfd = openConnection(urlStruct->host, 21)) == -1) {
        perror("socket");
        return -1;
    }
    
    sockResponse response;
    int size = readResponse(sockfd, &response);
    
    if (response.code != SERVICE_READY_FOR_NEW_USER) {
        printf("Error: %s when trying to\n", response.response);
        return -1;
    }

    

    
    return 0;
}


