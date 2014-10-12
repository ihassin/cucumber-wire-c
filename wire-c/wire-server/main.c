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
	int port = 3901;
	int ret_val;
	wire_context *context = 0;

	context = malloc(sizeof(context));
	context->port = port;
	context->logger = my_logger;
	context->listener = wire_listener_default;
	context->single_scenario = 1;

	ret_val = wire_server(context);
	return(ret_val);
}
