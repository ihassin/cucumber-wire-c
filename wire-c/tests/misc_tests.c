#ifndef __UNITY_TESTS_H__
#include "unity_tests.h"
#endif

void returns_a_version_string(void)
{
	char *version = wire_version();
    TEST_ASSERT_TRUE(version && *version);
}
