#ifndef __TOKEN_HANDLING_H__
#define __TOKEN_HANDLING_H__

int getIDToInvoke(char *buffer);
char *getNameToMatch(char *buffer);
char *getSnippetToMatch(char *buffer);
char *getVar(char *buffer);
int getVarPosition(char *buffer, char *var);
char *getCucumberVar(char *buffer);

#endif
