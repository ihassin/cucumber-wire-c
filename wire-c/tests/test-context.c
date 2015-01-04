#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_CONTEXT	1
#ifndef __TEST_CONTEXT_H__
#include "test-context.h"
#endif

void tests_my_logger(char *log)
{
	printf("Logger: %s\n", log);
}

void setUp(void)
{
	context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->logger = tests_my_logger;
	context->port = 3901;
}

void tearDown(void)
{
    free(context);
    context = 0;
}
