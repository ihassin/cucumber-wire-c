#include <stdlib.h>
#include <string.h>

#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

void my_logger(char *log)
{
	printf("Logger: %s\n", log);
}

int begin_callback(struct wire_context *context)
{
	printf("begin_callback called\n");
	return(0);
}

int end_callback(struct wire_context *context)
{
	printf("end_callback called\n");
	return(0);
}

int main(int argc, char **argv)
{
	int ret_val;
	wire_context *context;

	context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));

	context->port 				= atoi(argv[1]);
	context->single_scenario 	= atoi(argv[2]);
	context->logger 			= my_logger;
	context->begin_callback 	= begin_callback;
	context->end_callback 		= end_callback;
	context->listener 			= (wire_listener) wire_listener_default;

	ret_val = wire_server(context);
	return(ret_val);
}
