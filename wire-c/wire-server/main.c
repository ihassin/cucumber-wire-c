#include <stdlib.h>
#include <stdio.h>

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

void my_logger(char *log)
{
	printf("Logger: %s\n", log);
}

int main(int argc, char **argv)
{
	int ret_val;
	wire_context *context;

	context = malloc(sizeof(context));
	context->port = atoi(argv[1]);
	context->single_scenario = atoi(argv[2]);
	context->logger = my_logger;
	context->listener = wire_listener_default;

	ret_val = wire_server(context);
	return(ret_val);
}
