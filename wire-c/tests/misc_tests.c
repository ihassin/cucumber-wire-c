#ifndef __MISC_TESTS_H__
#include "misc_tests.h"
#endif

void returns_a_version_string(void)
{
	char *version = wire_version();
    TEST_ASSERT_TRUE(version && *version);
}
