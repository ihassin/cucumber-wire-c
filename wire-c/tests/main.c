//
//  main.c
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

int main(void)
{
    UnityBegin("main.c");

    // Listening on requested port
    RUN_TEST(returns_a_version_string);

	// Valid port numbers    
    RUN_TEST(accepts_valid_port_number);
    RUN_TEST(rejects_negative_port_number);
    RUN_TEST(rejects_zero_port_number);

    // Listening on requested port
    RUN_TEST(listens_on_requested_port);

    // Handle request tests
    RUN_TEST(rejects_null_context);
    RUN_TEST(rejects_null_buffer);
    RUN_TEST(rejects_empty_buffer);
    RUN_TEST(returns_fail_for_unknown_request);
    RUN_TEST(returns_success_for_known_request);
    RUN_TEST(returns_success_without_begin_callback);
    RUN_TEST(returns_success_without_end_callback);
    RUN_TEST(returns_success_with_begin_callback);
    RUN_TEST(returns_success_with_end_callback);
    RUN_TEST(returns_fail_with_neg_end_callback);
    RUN_TEST(returns_fail_with_neg_begin_callback);
    RUN_TEST(handle_callback_null_context);

    // Step Match tests
    RUN_TEST(step_match_callback_no_call_with_no_buffer);
    RUN_TEST(step_match_callback_no_call_with_null_buffer);
    RUN_TEST(handle_step_match_no_params);

    return UnityEnd();
}
