#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

static char name[1024];

void copyStr(char *to, char *from, char *end)
{
    while(from < end)
    {
        *to++ = *from++;
    }
    *to = 0;
}

char *getPastToken(char *buffer, char *token)
{
    char *ptr = strstr(buffer, token);
    ptr += strlen(token);
    return(ptr);
}

// ["invoke",{"id":"1","args":[]}]
int getIDToInvoke(char *buffer)
{
    if(!buffer || !*buffer)
    {
        return(-1);
    }
    *name = 0;
    char *namePtr = name;
    char *ptr = getPastToken(buffer, "\"invoke\"");
    ptr = strstr(ptr, ":") + 1;
    ptr = strstr(ptr, "\"") + 1;
    char *end = strstr(ptr, "\"");
    copyStr(namePtr, ptr, end);
    return(atoi(name));
}

// ["step_matches",{"name_to_match":"we're all wired"}]
char *getNameToMatch(char *buffer)
{
    if(!buffer || !*buffer)
    {
        return("");
    }
    *name = 0;
    char *namePtr = name;
    char *ptr = getPastToken(buffer, "\"name_to_match\"");

    ptr = strstr(ptr, "\"") + 1;
    char *end = strstr(ptr, "\"");
    copyStr(namePtr, ptr, end);
    return(name);
}

// ["snippet_text",{"step_keyword":"Given","step_name":"wire server is running","multiline_arg_class":""}]
char *getSnippetToMatch(char *buffer)
{
    *name = 0;
    char *namePtr = name;
    char *ptr = getPastToken(buffer, "\"step_name\"");

    ptr = strstr(ptr, "\"") + 1;
    char *end = strstr(ptr, "\"");
    copyStr(namePtr, ptr, end);
    return(name);
}
