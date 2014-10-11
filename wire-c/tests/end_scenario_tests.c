#include <pthread.h>
#include <assert.h>

#ifndef __UNITY_TESTS_H__
#include "unity_tests.h"
#endif

#ifndef __TCP_CLIENT_H__
#include "tcp_client.h"
#endif

char *end_scenario_injector(void)
{
    return("[\"end_scenario\"]\n");
}

char *end_scenario_dejector(void)
{
    return("[\"success\", []]\n");
}

void recognises_end_scenario(void)
{
    context->packet_injector = end_scenario_injector;
    context->packet_dejector = end_scenario_dejector;
	context->port = 3901;
    context->listener = wire_listener_default;
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
