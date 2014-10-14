#ifndef __API_H__
#define __API_H__

int api_match_name(char* name);

typedef int (*api_function) (void *);

typedef struct function_table
{
	char api_name[1024];
	api_function api;
} APITable;

#endif
