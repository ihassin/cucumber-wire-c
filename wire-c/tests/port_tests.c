#ifndef __PORT_TESTS_H__
#include "port_tests.h"
#endif

void accepts_valid_port_number(void)
{
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
    TEST_ASSERT_EQUAL(0, wire_server(context));
}
