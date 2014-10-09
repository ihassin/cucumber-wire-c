#include <stdlib.h>

#include "wire-server.h"

int main(int argc, char **argv)
{
	int port = 3901;
	int ret_val;
	wire_context *context = 0;

	context = malloc(sizeof(context));
	ret_val = wire_server(context);
	return(ret_val);
}
