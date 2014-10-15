#include <string.h>
#include <stdio.h>

#ifndef __API_H__
#include "api.h"
#endif

APITable api_table[] = {
	{ "wire server is running", start_wire_server 		},
	{ "I run this scenario", 	run_scenario 			},
	{ "it responds correctly", 	respond_to_scenario		},
	0
};

int invoke_by_id(int id, void *context)
{
	int tableSize = sizeof(api_table)/sizeof(APITable);

	if (id < tableSize)
	{
		printf("Calling %s\n", api_table[id].api_name);
		return((api_table[id].api) (context));
	}
	return(-1);
}

int api_match_name(char* name)
{
	int idx = 0;
	int tableSize = sizeof(api_table)/sizeof(APITable);

	while(idx < tableSize)
	{
		if(strcmp(name, api_table[idx].api_name) == 0)
		{
			return(idx);
		}
		idx++;
	}
	return(-1);
}

int start_wire_server(void *data)
{
	return(0);
}

int run_scenario(void *data)
{
	return(0);
}

int respond_to_scenario(void *data)
{
	return(0);
}
