//
//  main.c
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#include <stdlib.h>
#include "unity.h"
#include "wire-server.h"

void logger(char *log)
{
	printf("Logger: %s\n", log);
}

void correctly_processes_port_number(void)
{
	wire_context *context = malloc(sizeof(wire_context));
	context->port = 3901;
	context->logger = logger;
    TEST_ASSERT_EQUAL(0, wire_server(context));
    free(context);
}

void rejects_negative_port_number(void)
{
	wire_context *context = malloc(sizeof(wire_context));
	context->port = -3901;
    TEST_ASSERT_EQUAL(1, wire_server(context));
    free(context);
}

void rejects_zero_port_number(void)
{
	wire_context *context = malloc(sizeof(wire_context));
	context->port = 0;
    TEST_ASSERT_EQUAL(1, wire_server(context));
    free(context);
}

int main(void)
{
    UnityBegin("main.c");
    
    RUN_TEST(correctly_processes_port_number);
    RUN_TEST(rejects_negative_port_number);
    RUN_TEST(rejects_zero_port_number);

    UnityEnd();
}
