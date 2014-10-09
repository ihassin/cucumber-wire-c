#include <stdlib.h>
#include <stdio.h>

#include "wire-server.h"

void logger(char *log)
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
	context->logger = logger;

	ret_val = wire_server(context);
	return(ret_val);
}
