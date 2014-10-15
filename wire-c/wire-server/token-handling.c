#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

// ["invoke",{"id":"1","args":[]}]
int getIDToInvoke(char *buffer)
{
    static char name[1024];
    char *namePtr = name;

    char *token = "\"invoke\"";
    char *ptr = strstr(buffer, token);
    ptr += strlen(token);
    ptr = strstr(ptr, ":") + 1;
    ptr = strstr(ptr, "\"") + 1;
    char *end = strstr(ptr, "\"");
    while(ptr < end)
    {
        *namePtr++ = *ptr++;
    }
    *namePtr = 0;
    return(atoi(name));
}

// ["step_matches",{"name_to_match":"we're all wired"}]
char *getNameToMatch(char *buffer)
{
    static char name[1024];
    char *namePtr = name;

    char *token = "\"name_to_match\"";
    char *ptr = strstr(buffer, token);
    ptr += strlen(token);
    ptr = strstr(ptr, "\"") + 1;
    char *end = strstr(ptr, "\"");
    while(ptr < end)
    {
        *namePtr++ = *ptr++;
    }
    *namePtr = 0;
    return(name);
}

// ["snippet_text",{"step_keyword":"Given","step_name":"wire server is running","multiline_arg_class":""}]
char *getSnippetToMatch(char *buffer)
{
    static char name[1024];
    char *namePtr = name;

    char *token = "\"step_name\"";
    char *ptr = strstr(buffer, token);
    ptr += strlen(token);
    ptr = strstr(ptr, "\"") + 1;
    char *end = strstr(ptr, "\"");
    while(ptr < end)
    {
        *namePtr++ = *ptr++;
    }
    *namePtr = 0;
    return(name);
}
