#ifndef __UNITY_TESTS_H__
#define __UNITY_TESTS_H__

#include "unity.h"

#ifndef __PORT_TESTS_H__
#include "port_tests.h"
#endif

#ifndef __MISC_TESTS_H__
#include "misc_tests.h"
#endif

#ifndef __HANDLE_REQUEST_TESTS_H__
#include "handle_request_tests.h"
#endif

void *client_thread_routine(void *data);

#endif
