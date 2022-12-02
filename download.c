#include <stdio.h>
#include "URL.h"

int main(void)
{
    const char text[] = "ftp://user:passs@cboard.cprogramming.com/ola/online.php";
    
    url urlStruct;

    parseURL(text, &urlStruct);

    return 0;

}