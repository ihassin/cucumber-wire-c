#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

void returns_a_version_string(void)
{
	char *version = wire_version();
    TEST_ASSERT_TRUE(version && *version);
}
