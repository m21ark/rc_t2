#include <stdio.h>
#include "URL.h"

int main(int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: ./download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(1);
    }
    
    url urlStruct;

    if (parseURL(argv[1], &urlStruct) != 0) {
        fprintf(stderr, "There was an error passing the url");
        exit(1);
    }

    
    

    return 0;

}