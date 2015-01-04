#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#include <pthread.h>
#include <assert.h>

#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

#ifndef __TCP_CLIENT_H__
#include "tcp-client.h"
#endif

#ifndef __TEST_CONTEXT_H__
#include "test-context.h"
#endif

void logger (char *log)
{
    printf("Loogged <%s>\n", log);
}

int dummy_listener(wire_context *context)
{
    printf("dummy_listener called\n");
    return(0);
}

void accepts_valid_port_number(void)
{
	context->listener = dummy_listener;
    context->logger = 0;
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
    context->logger = 0;
    TEST_ASSERT_EQUAL(1, wire_server(context));
}

void *client_thread_routine(void *data)
{
    wire_context *context = (wire_context *) data;
    (*context->listener) (context);
    pthread_exit(context);
    return(0);
}

char *injector(wire_context *context)
{
    return("hi\n");
}

char *dejector(wire_context *context)
{
    return("[\"fail\",{\"message\":\"Cucumber sent us an unknown command\"}]\n");
}

void listens_on_requested_port(void)
{
	context->port = 3901;
    context->listener = wire_listener_default;
    context->packet_injector = injector;
    context->packet_dejector = dejector;
    context->logger = 0;
    context->single_scenario = 1;
    context->begin_callback         = 0;
    context->end_callback           = 0;
    context->step_match_callback    = 0;

    // Create the thread using POSIX routines.
    pthread_attr_t  attr;
    pthread_t       posixThreadID;
    int             retVal;
 
    retVal = pthread_attr_init(&attr);
    assert(!retVal);

    retVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    assert(!retVal);
 
    int threadError = pthread_create(&posixThreadID, &attr, &client_thread_routine, context);
 
    retVal = pthread_attr_destroy(&attr);
    assert(!retVal);
    if (threadError != 0)
    {
        printf("ThreadError %d\n", retVal);
    }

    retVal = tcp_client(context);
    printf("tcp_client %d\n", retVal);

    void *status;
    pthread_join(posixThreadID, &status);
    TEST_ASSERT_EQUAL(0, retVal);
}
