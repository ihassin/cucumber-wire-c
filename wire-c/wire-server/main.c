#include <stdio.h>

#include "wire-server.h"

int main(int argc, char **argv)
{
	int port = 3901;
	int verbose = 1;
	int ret_val;

	ret_val = wire_server(port, verbose);
	return(ret_val);
}
