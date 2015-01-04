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
    RUN_TEST(handle_invoke_underscript);
    RUN_TEST(handle_invoke_overscript);
    RUN_TEST(handle_invoke_rightscript);

    // Step Match tests
    RUN_TEST(step_match_callback_no_call_with_no_buffer);
    RUN_TEST(step_match_callback_no_call_with_null_buffer);
    RUN_TEST(handle_step_match_no_params);
    RUN_TEST(handle_step_match_not_found);

    // Buffer tests
    RUN_TEST(get_begin_request);
    RUN_TEST(get_begin_end_request);
    
    // Token extraction: INVOKE
    RUN_TEST(finds_an_invoke_request);
    RUN_TEST(finds_an_invoke_request_irregular);
    RUN_TEST(finds_an_invoke_request_irregular_4_digit);    

    // Token extraction: MATCH
    RUN_TEST(finds_a_name_to_match);
    RUN_TEST(finds_a_name_to_match_irregular);
    RUN_TEST(handles_empty_invoke_request);
    RUN_TEST(handles_empty_match_request);

    // Cucumber var handling
    RUN_TEST(finds_gherkin_var);
    RUN_TEST(does_not_find_gherkin_var_when_missing);
    RUN_TEST(does_not_find_gherkin_var_when_null);
    RUN_TEST(does_not_find_gherkin_var_when_empty);
    RUN_TEST(does_not_find_gherkin_var_when_in_double_quotes);

    // JSON args
    RUN_TEST(finds_json_arg);

    return UnityEnd();
}
