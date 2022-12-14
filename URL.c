#include "URL.h"

int parseURL(const char *urlString, url *urlStruct)
{
    size_t maxGroups = 6;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    int reti;
    char *re = "ftp://(([a-z0-9]+):([a-z0-9]+)@)?([\\.a-z0-9]+)/([\\./a-z0-9-]+)$";

    printf("HERE\n");

    if (regcomp(&regexCompiled, re, REG_EXTENDED))
    {
        fprintf(stderr, "Could not compile regular expression.\n");
        return 1;
    };

    if (regexec(&regexCompiled, urlString, maxGroups, groupArray, 0) == 0)
    {
    printf("HERE\n");

        unsigned int g = 0, optional = 0;
        for (g = 0; g < maxGroups; g++)
        {
            optional = 0;
            if (groupArray[g].rm_so == (size_t)-1)
                optional = 1; // No more groups

            char sourceCopy[strlen(urlString) + 1];
            strcpy(sourceCopy, urlString);
            sourceCopy[groupArray[g].rm_eo] = 0;

            if (optional) 
            {
                if (g == 2)
                    strcpy(urlStruct->user, "anonymous");
                else if (g == 3)
                    strcpy(urlStruct->password, "password");
                continue;
            }

            printf("Group %u: [%2u-%2u]: %s\n",
                   g, groupArray[g].rm_so, groupArray[g].rm_eo,
                   sourceCopy + groupArray[g].rm_so);

            if (g == 2)
                strcpy(urlStruct->user, sourceCopy + groupArray[g].rm_so);
            else if (g == 3)
                strcpy(urlStruct->password, sourceCopy + groupArray[g].rm_so);
            else if (g == 4)
                strcpy(urlStruct->host, sourceCopy + groupArray[g].rm_so);
            else if (g == 5)
                strcpy(urlStruct->path, sourceCopy + groupArray[g].rm_so);
        }
    }

    regfree(&regexCompiled);
    return 0;
}

