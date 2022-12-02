#include "URL.h"

int parseURL(const char *urlString, url *urlStruct)
{
    char user[512];
    char password[512];
    char protocol[512];
    char host[512];
    char path[512];
    char file[512];
    size_t maxGroups = 6;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    int reti;
    char *re = "ftp://(([a-z0-9]+):([a-z0-9]+)@)?([\\.a-z0-9]+)/([\\./a-z0-9]+)$";

    if (regcomp(&regexCompiled, re, REG_EXTENDED))
    {
        printf("Could not compile regular expression.\n");
        return 1;
    };

    if (regexec(&regexCompiled, urlString, maxGroups, groupArray, 0) == 0)
    {
        unsigned int g = 0;
        for (g = 0; g < maxGroups; g++)
        {
            if (groupArray[g].rm_so == (size_t)-1)
                break; // No more groups

            char sourceCopy[strlen(urlString) + 1];
            strcpy(sourceCopy, urlString);
            sourceCopy[groupArray[g].rm_eo] = 0;

            printf("Group %u: [%2u-%2u]: %s\n",
                   g, groupArray[g].rm_so, groupArray[g].rm_eo,
                   sourceCopy + groupArray[g].rm_so);

            if (g == 2)
                strcpy(user, sourceCopy + groupArray[g].rm_so);
            else if (g == 3)
                strcpy(password, sourceCopy + groupArray[g].rm_so);
            else if (g == 4)
                strcpy(host, sourceCopy + groupArray[g].rm_so);
            else if (g == 5)
                strcpy(path, sourceCopy + groupArray[g].rm_so);
        }
    }

    regfree(&regexCompiled);
    return 0;
}

