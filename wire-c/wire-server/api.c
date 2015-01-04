#include <string.h>
#include <stdio.h>

#ifndef __API_H__
#include "api.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

APITable api_table[] = {
	{ "wire server is running", 				start_wire_server 		}
	, { "I run this scenario", 					run_scenario 			}
	, { "it responds correctly", 				respond_to_scenario		}
	, { "this 'scenario' is run", 				param_scenario_run		}
	, { "'scenario' is parsed as a variable", 	scenario_as_variable 	}
	, 0
};

int invoke_by_id(int id, void *context)
{
	int tableSize = sizeof(api_table)/sizeof(APITable);

	if (id < tableSize)
	{
		wire_context *ctx = (wire_context *) context;
		if(ctx->logger)
		{
			char buffer[1128];
			sprintf(buffer, "Calling %s\n", api_table[id].api_name);
			(*ctx->logger) (buffer);
		}
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

// <["invoke",{"id":"3","args":["scenario"]}]>
int param_scenario_run(void *data)
{
	wire_context *context = (wire_context *) data;
	char *var = getJSONArg(context->incoming);
	if(context->logger)
	{
		char buffer[1128];
		sprintf(buffer, "API: param_scenario_run: running with %s\n", var);
		(*context->logger) (buffer);
	}
	return(0);
}

// <["invoke",{"id":"3","args":["scenario"]}]>
int scenario_as_variable(void *data)
{
	wire_context *context = (wire_context *) data;
	char *var = getJSONArg(context->incoming);
	if(context->logger)
	{
		char buffer[1128];
		sprintf(buffer, "API: scenario_as_variable: running with %s\n", var);
		(*context->logger) (buffer);
	}
	return(0);
}


