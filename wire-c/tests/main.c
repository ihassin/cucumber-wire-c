//
//  main.c
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#ifndef __UNITY_TESTS_H__
#include "unity_tests.h"
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

    return UnityEnd();
}
