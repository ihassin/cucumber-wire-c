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

APITable test_api_table[] = {
    { "wire server is running", 				start_wire_server 		}
    , 0
};

static int was_called = 0;

static int test_step_match_callback(wire_context *context)
{
    was_called = 0;

//    TEST_ASSERT_EQUAL_STRING("wire server is running", context->request_block.step_match.name_to_match);

    int id = api_match_name(context, context->request_block.step_match.name_to_match);
    if(id >= 0)
    {
        sprintf(context->outgoing, "[\"success\",[{\"id\":\"%d\", \"args\":[]}]]\n", id);
        was_called = 1;
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
    context->step_match_callback = test_step_match_callback;

    handleRequest(0, context);
    TEST_ASSERT_EQUAL(0, was_called);
    was_called = 0;
}

void step_match_callback_no_call_with_null_buffer(void)
{
    was_called = 0;
    wire_context *context = malloc(sizeof(wire_context));
    memset(context, 0, sizeof(wire_context));
    context->step_match_callback = test_step_match_callback;

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
    context->step_match_callback = test_step_match_callback;
    context->api_table = test_api_table;

    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT_EQUAL(1, was_called);
    TEST_ASSERT(strstr(buffer, "success"));

    was_called = 0;
}

void handle_step_match_not_found(void)
{
    char buffer[1024];
    
    was_called = 0;
    strcpy(buffer, "[\"step_matches\",{\"name_to_match\":\"mikey mouse\"}]\n");
    
    wire_context *context = malloc(sizeof(wire_context));
    memset(context, 0, sizeof(wire_context));
    context->step_match_callback = test_step_match_callback;
    context->api_table = test_api_table;
    
    TEST_ASSERT_EQUAL(0, handleRequest(buffer, context));
    TEST_ASSERT_EQUAL(0, was_called);
    TEST_ASSERT(strstr(buffer, "fail"));
    
    was_called = 0;
}

