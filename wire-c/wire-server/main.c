#include <stdlib.h>
#include <string.h>

#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifndef __API_H__
#include "api.h"
#endif

void my_logger(char *log)
{
	printf("Logger: %s\n", log);
}

int begin_callback(struct wire_context *context)
{
	return(0);
}

int end_callback(struct wire_context *context)
{
	return(0);
}

int step_match_callback(wire_context *context)
{
	int retVal = api_match_name(context->request_block.step_match.name_to_match);

	if (retVal == -1)
	{
		sprintf(context->outgoing, "[\"success\", []]\n");
	}
	else
	{
		sprintf(context->outgoing, "[\"success\",[{\"id\":\"%d\", \"args\":[]}]]\n", retVal);
	}
	return(0);
}

int step_snippet_callback(wire_context *context)
{
	int retVal = api_match_name(context->request_block.step_match.name_to_match);

	if (retVal == -1)
	{
		sprintf(context->outgoing, "[\"success\", []]\n");
	}
	else
	{
		sprintf(context->outgoing, "[\"success\",[\"int %s(void) { return %d; } \"]]\n", context->request_block.step_match.name_to_match, retVal);
	}
	return(0);
}

int invoke_callback(wire_context *context)
{
	if(context->logger)
	{
		char buffer[100];
		sprintf(buffer, "Invoking %d\n", context->request_block.step_invoke.id);
		(*context->logger) (buffer);
	}

	return(invoke_by_id(context->request_block.step_invoke.id, (void *) context));
}

int main(int argc, char **argv)
{
	int retVal;
	wire_context *context;

	context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));

	context->port 					= atoi(argv[1]);
	context->single_scenario 		= atoi(argv[2]);
	context->logger 				= atoi(argv[3]) == 1 ? my_logger : 0;
	context->begin_callback 		= begin_callback;
	context->end_callback 			= end_callback;
	context->listener 				= (wire_listener) wire_listener_default;
	context->step_match_callback 	= step_match_callback;
	context->invoke_callback 		= invoke_callback;
	context->step_snippet_callback 	= step_snippet_callback;

	retVal = wire_server(context);
	return(retVal);
}
