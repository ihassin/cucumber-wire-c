#include <stdlib.h>

#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __HANDLE_STEP_MATCH_TESTS_H__
#include "handle-step-match-tests.h"
#endif

#ifndef __API_H__
#include "api.h"
#endif

#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

static int was_called = 0;

int step_match_callback(wire_context *context)
{
	was_called = 1;

	TEST_ASSERT_EQUAL_STRING("wire server is running", context->request_block.step_match.name_to_match);

	int id = api_match_name(context->request_block.step_match.name_to_match);
	if(id >= 0)
	{
		sprintf(context->outgoing, "[\"success\",[{\"id\":\"%d\", \"args\":[]}]]\n", id);
	}
	else
	{
		sprintf(context->outgoing, "[\"fail\",{\"message\":\"api does not support %s\"}]\n", context->request_block.step_match.name_to_match);
	}
	return(0);
}

int invoke_callback(wire_context *context)
{
	was_called = 1;

	TEST_ASSERT_EQUAL_STRING("set_alarm_on", context->request_block.step_match.name_to_match);

	int id = api_match_name(context->request_block.step_match.name_to_match);
	if(id >= 0)
	{
		sprintf(context->outgoing, "[\"success\",[{\"id\":\"%d\", \"args\":[]}]]\n", id);
	}
	else
	{
		sprintf(context->outgoing, "[\"fail\",{\"message\":\"api does not support %s\"}]\n", context->request_block.step_match.name_to_match);
	}
	return(0);
}

void step_match_callback_no_call_with_no_buffer(void)
{
    was_called = 0;
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->step_match_callback = step_match_callback;

	handleRequest(0, context);
    TEST_ASSERT_EQUAL(0, was_called);
    was_called = 0;
}

void step_match_callback_no_call_with_null_buffer(void)
{
    was_called = 0;
	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->step_match_callback = step_match_callback;

	handleRequest("", context);
    TEST_ASSERT_EQUAL(0, was_called);
    was_called = 0;
}

void handle_step_match_no_params(void)
{
	char buffer[1024];

    was_called = 0;
	strcpy(buffer, "[\"step_matches\",{\"name_to_match\":\"wire server is running\"}]\n");

	wire_context *context = malloc(sizeof(wire_context));
	memset(context, 0, sizeof(wire_context));
	context->step_match_callback = step_match_callback;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT_EQUAL(1, was_called);
    TEST_ASSERT(strstr(buffer, "success"));

    was_called = 0;
}
