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
      { "I run this scenario",                  run_scenario 			}
    , { "it responds correctly",                respond_to_scenario     }
    , { "this 'scenario' is run",               param_scenario_run		}
    , { "'scenario' is parsed as a variable", 	scenario_as_variable 	}
    , { "wire server is running",               start_wire_server 		}
    , 0
};

int start_wire_server(struct wire_context *context)
{
	return(0);
}

int run_scenario(struct wire_context *context)
{
	return(0);
}

int respond_to_scenario(struct wire_context *context)
{
	return(0);
}

// <["invoke",{"id":"3","args":["scenario"]}]>
int param_scenario_run(struct wire_context *context)
{
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
int scenario_as_variable(struct wire_context *context)
{
	char *var = getJSONArg(context->incoming);
	if(context->logger)
	{
		char buffer[1128];
		sprintf(buffer, "API: scenario_as_variable: running with %s\n", var);
		(*context->logger) (buffer);
	}
	return(0);
}


