//
//  main.c
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#include "unity.h"

#ifndef __PORT_TESTS_H__
#include "port_tests.h"
#endif

int main(void)
{
    UnityBegin("main.c");

	// Valid port numbers    
    RUN_TEST(accepts_valid_port_number);
    RUN_TEST(rejects_negative_port_number);
    RUN_TEST(rejects_zero_port_number);

    // Listening on requested port
    RUN_TEST(listens_on_requested_port);
    return UnityEnd();
}
