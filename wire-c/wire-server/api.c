#include <string.h>

#ifndef __API_H__
#include "api.h"
#endif

int set_alarm_on(void *data);

APITable api_table[] = {
	{ "set_alarm_on", set_alarm_on },
	0
};

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
	}
	return(-1);
}

int set_alarm_on(void *data)
{
	return(0);
}
