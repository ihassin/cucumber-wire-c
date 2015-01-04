#include <stdlib.h>
#include <string.h>

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifndef __HANDLE_REQUEST_TESTS_H__
#include "handle-request-tests.h"
#endif

#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

static int test_begin_callback(struct wire_context *context)
{
    return(0);
}

static int test_end_callback(struct wire_context *context)
{
    return(0);
}

static int test_begin_callback_neg(struct wire_context *context)
{
    return(1);
}

static int test_end_callback_neg(struct wire_context *context)
{
    return(1);
}

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

void returns_success_with_begin_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->begin_callback = test_begin_callback;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

void returns_success_with_end_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->end_callback = test_end_callback;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}

void returns_fail_with_neg_begin_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"begin_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->begin_callback = test_begin_callback_neg;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void returns_fail_with_neg_end_callback(void)
{
	char buffer[1024];

	strcpy(buffer, "[\"end_scenario\"]\n");
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->end_callback = test_end_callback_neg;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void handle_callback_null_context(void)
{
	char *ptr = handle_callback(test_begin_callback_neg, 0);
    TEST_ASSERT(strstr(ptr, "fail"));
}

static int start_wire_server(struct wire_context *context)
{
    return (0);
}

static APITable test_api_table[] = {
    { "wire server is running", 				start_wire_server 		}
    , 0
};

int test_invoke_callback(wire_context *context)
{
    return(invoke_by_id(context->request_block.step_invoke.id, context));
}

void handle_invoke_underscript(void)
{
    char buffer[1024];
    
    strcpy(buffer, "[\"invoke\",{\"id\":\"-1\",\"args\":[]}]\n");
    wire_context *context = malloc(sizeof(wire_context));
    memset(context, 0, sizeof(wire_context));
    context->api_table       = test_api_table;
    context->invoke_callback = test_invoke_callback;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void handle_invoke_overscript(void)
{
    char buffer[1024];
    
    strcpy(buffer, "[\"invoke\",{\"id\":\"100\",\"args\":[]}]\n");
    wire_context *context = malloc(sizeof(wire_context));
    memset(context, 0, sizeof(wire_context));
    context->api_table       = test_api_table;
    context->invoke_callback = test_invoke_callback;
    
    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "fail"));
}

void handle_invoke_rightscript(void)
{
    char buffer[1024];
    
    strcpy(buffer, "[\"invoke\",{\"id\":\"0\",\"args\":[]}]\n");
    wire_context *context = malloc(sizeof(wire_context));
    memset(context, 0, sizeof(wire_context));
    context->api_table       = test_api_table;
    context->invoke_callback = test_invoke_callback;
    
    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT(strstr(buffer, "success"));
}
