#include <stdio.h>
#include <stdlib.h>

#define ALLOC_CONTEXT	1
#ifndef __CONTEXT_H__
#include "context.h"
#endif

void logger(char *log)
{
	printf("Logger: %s\n", log);
}

void setUp(void)
{
	context = malloc(sizeof(wire_context));
	context->logger = logger;
	context->port = 3901;
}

void tearDown(void)
{
    free(context);
    context = 0;
}
