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

    if (login(sockfd, urlStruct->user, urlStruct->password)) {
        printf("Error in login\n");
        return -1;
    }

    if (passiveMode(sockfd, &response))
    {
        printf("Error entering Passive Mode\n");
        return -1;
    }
    
    if (requestFile(sockfd, response.ip, response.port, urlStruct->path))
    {
        perror("It was not possible to download the file");
        return -1;
    }


    if (close(sockfd) < 0) {
        perror("Error closing command socket!\n");
        return -1;
    }
    
    return 0;
}


int requestFile(int sockfd, char * ip, int port, char * path) {
    // Open a connection to the server with response.ip and response.port
    int dataSockfd;
    if ((dataSockfd = openConnection(ip, port)) == -1) { // NOTA... aqui já se passa o ip em vez do host
        perror("socket");
        return -1;
    }

    // Send RETR command
    sockCommand cmd = {RETR, ""};
    strcpy(cmd.argument, path);
    if (sendCommand(sockfd, &cmd) < 0)
    {
        perror("Error sending RETR cmd");
        return -1;
    }

    sockResponse response;
    int size = readResponse(sockfd, &response);

    if (response.code != FILE_OK_RETR_READY)
    {
        perror("It's not possible to transfer the file");
        return -1;
    }
    
    fflush(stdout);
    printf("Downloading file...\n");

    saveFile(dataSockfd, "OLA.txt"); // get FILENAME

    int rZide = readResponse(sockfd, &response); // TODO ::: APARECE UMAS RESPOSTAS REPETIDAS EM ALGUNS SITIOS....ver dps
    if (response.code != TRANSFER_COMPLETE) // TODO: PERGUNTAR AO STOR O PK DA NOTA DOS SLIDES
    {
        perror("Error closing data connection");
        return -1;
    }

    if (close(dataSockfd) < 0) {
        perror( "Error closing data socket!\n");
        return -1;
    }

    return 0;
}

int saveFile(int dataSockfd, char * filename) {
    int fd;
    if ((fd = open(filename, O_WRONLY | O_CREAT)) < 0) {
        perror("Error creating or opening the file");
        return -1;
    }

    // TODO : salvar no ficheiro criado/aberto
    sockResponse response; // AQUI N CONVÉM USAR O response por causa do tamanho do ficheiro
    int size = readResponse(dataSockfd, &response); // AQUI N CONVÉM USAR O response por causa do tamanho do ficheiro

    printf("------------------\n%s\n------------------\n", response.response);

    if (close(fd) < 0) {
        perror("Error closing File!\n");
        return -1;
    }
}

int getFileName(char * path, char * filename) {

    // Get filename from path

    // TODO: IR BUSCAR O NOME DO FILE AO PATH para guardar com o mesmo nome no diretório do utilizador
    return 0;
}

