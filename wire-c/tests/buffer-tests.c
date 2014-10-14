#include <stdlib.h>
#include <string.h>

#ifndef __BUFFER_TESTS_H__
#include "buffer-tests.h"
#endif

#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

static char incoming[1024];
static int incomingCounter = 0;

int myGetByte(int socket, char *buffer)
{
	if(incomingCounter < (sizeof(incoming) - 1))
	{
		*buffer = incoming[incomingCounter++];
		return 1;
	}
	return(0);
}

void get_begin_request(void)
{
	char request[1024];

	incomingCounter = 0;
	strcpy(incoming, "[\"begin_scenario\"]\n");

	int retVal = getRequest(myGetByte, -1, request, sizeof(request));

    TEST_ASSERT_EQUAL(strlen(incoming) - 1, retVal);
}

void get_begin_end_request(void)
{
	char request[1024];

	incomingCounter = 0;
	strcpy(incoming, "[\"begin_scenario\"]\n[\"end_scenario\"]\n");

	int retVal = getRequest(myGetByte, -1, request, sizeof(request));

    TEST_ASSERT_EQUAL(18, retVal);

	retVal = getRequest(myGetByte, -1, request, sizeof(request));

    TEST_ASSERT_EQUAL(16, retVal);
}
