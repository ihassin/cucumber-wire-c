//
//  main.c
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#include <stdio.h>
#include "unity.h"
#include "wire-server.h"

void test_1(void)
{
    TEST_ASSERT_EQUAL(0, wire_server(3901, 1));
}

int main(void)
{
    UnityBegin("main.c");
    
    RUN_TEST(test_1);

    UnityEnd();
    return 0;
}
