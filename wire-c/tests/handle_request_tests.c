#include <stdlib.h>
#include <string.h>

#ifndef __HANDLE_REQUEST_TESTS_H__
#include "handle_request_tests.h"
#endif

#ifndef __UNITY_TESTS_H__
#include "unity_tests.h"
#endif

void rejects_null_context(void)
{
    TEST_ASSERT_EQUAL(1, handleRequest("buffer", 0));
}

void rejects_null_buffer(void)
{
	wire_context *context = malloc(sizeof(wire_context));
    TEST_ASSERT_EQUAL(1, handleRequest(0, context));
}

void rejects_empty_buffer(void)
{
	wire_context *context = malloc(sizeof(wire_context));
    TEST_ASSERT_EQUAL(1, handleRequest("", context));
}

void returns_fail_for_unknown_request(void)
{
	char buffer[1024];

	strcpy(buffer, "yoo hoo\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void returns_success_for_known_request(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

void returns_success_without_begin_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

void returns_success_without_end_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

int begin_callback(struct wire_context *context)
{
	return(0);
}

int end_callback(struct wire_context *context)
{
	return(0);
}

void returns_success_with_begin_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->begin_callback = begin_callback;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

void returns_success_with_end_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->end_callback = end_callback;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

int begin_callback_neg(struct wire_context *context)
{
	return(1);
}

int end_callback_neg(struct wire_context *context)
{
	return(1);
}

void returns_fail_with_neg_begin_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->begin_callback = begin_callback_neg;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void returns_fail_with_neg_end_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"end_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->end_callback = end_callback_neg;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void handle_callback_null_context(void)
{
	char *ptr = handle_callback(begin_callback_neg, 0);
    TEST_ASSERT(strstr(ptr, "fail"));
}
