#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#include <pthread.h>
#include <assert.h>

#ifndef __UNITY_TESTS_H__
#include "unity_tests.h"
#endif

#ifndef __TCP_CLIENT_H__
#include "tcp_client.h"
#endif

#define LOG(m) { if (context->logger) (*context->logger) (m); }

int dummy_listener(int port, wire_logger logger, int loops)
{
    if(logger)
    {
        (*logger) ("Dummy listener called");
    }
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
    int ret_val = (*context->listener) (context->port, context->logger, context->loops);
    pthread_exit(data);
    return(0);
}

char *injector(void)
{
    return("hi\n");
}

char *dejector(void)
{
    return("[\"fail\"]\n");
}

void listens_on_requested_port(void)
{
	context->port = 3901;
    context->listener = wire_listener_default;
    context->packet_injector = injector;
    context->packet_dejector = dejector;
    context->logger = 0;
    context->loops = 1;

    // Create the thread using POSIX routines.
    pthread_attr_t  attr;
    pthread_t       posixThreadID;
    int             ret_val;
 
    ret_val = pthread_attr_init(&attr);
    assert(!ret_val);

    ret_val = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    assert(!ret_val);
 
    int threadError = pthread_create(&posixThreadID, &attr, &client_thread_routine, context);
 
    ret_val = pthread_attr_destroy(&attr);
    assert(!ret_val);
    if (threadError != 0)
    {
         // Report an error.
    }

    ret_val = tcp_client(context);
    void *status;
    pthread_join(posixThreadID, &status);
    TEST_ASSERT_EQUAL(0, ret_val);
}
