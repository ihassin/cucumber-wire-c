#ifndef __UNITY_TESTS_H__
#define __UNITY_TESTS_H__

#include "unity.h"

#ifndef __PORT_TESTS_H__
#include "port-tests.h"
#endif

#ifndef __MISC_TESTS_H__
#include "misc-tests.h"
#endif

#ifndef __HANDLE_REQUEST_TESTS_H__
#include "handle-request-tests.h"
#endif

#ifndef __HANDLE_STEP_MATCH_TESTS_H__
#include "handle-step-match-tests.h"
#endif

#ifndef __BUFFER_TESTS_H__
#include "buffer-tests.h"
#endif

#ifndef __TOKEN_HANDLING_TESTS_H__
#include "token-handling-tests.h"
#endif

#ifndef __VAR_TESTS_H__
#include "var-tests.h"
#endif

void *client_thread_routine(void *data);

#endif
