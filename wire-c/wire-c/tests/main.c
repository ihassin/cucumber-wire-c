//
//  main.c
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

char MessageBuffer[50];

extern void setUp(void);
extern void tearDown(void);

void test_1(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

int main(void)
{
    UnityBegin("main.c");
    
    RUN_TEST(test_1);

    UnityEnd();
    return 0;
}
