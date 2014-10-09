#ifndef __PORT_TESTS_H__
#include "port_tests.h"
#endif

int dummy_listener(int port, wire_logger logger)
{
    (*logger) ("Dummy listener called\n");
    return(0);
}

void accepts_valid_port_number(void)
{
	context->listener = dummy_listener;
    TEST_ASSERT_EQUAL(0, wire_server(context));
}

void rejects_negative_port_number(void)
{
	context->port = -3901;
    TEST_ASSERT_EQUAL(1, wire_server(context));
}

void rejects_zero_port_number(void)
{
	context->port = 0;
    TEST_ASSERT_EQUAL(1, wire_server(context));
}

void listens_on_requested_port(void)
{
	context->port = 3901;
    context->listener = wire_listener_default;
    context->listener = dummy_listener;
    
    // Idea is to run this in a thread
    int ret_val = (*context->listener) (context->port, context->logger);
    // Open a socket on 3901 and write hello
    // Expect hello to come back
    TEST_ASSERT_EQUAL(0, ret_val);
}
