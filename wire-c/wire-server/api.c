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
