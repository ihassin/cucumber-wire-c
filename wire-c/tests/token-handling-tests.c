#include <string.h>

#ifndef __TOKEN_HANDLING_TESTS_H__
#include "token-handling-tests.h"
#endif

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

void finds_an_invoke_request(void)
{
	static char buffer[1024];

	strcpy(buffer, "[\"invoke\",{\"id\":\"1\",\"args\":[]}]");
	
    TEST_ASSERT_EQUAL(1, getIDToInvoke(buffer));
}

void finds_an_invoke_request_irregular(void)
{
	static char buffer[1024];

	strcpy(buffer, "[\"invoke\" , { \"id\" : \"1\" ,\"args\":[]}]");
	
    TEST_ASSERT_EQUAL(1, getIDToInvoke(buffer));
}

void finds_an_invoke_request_irregular_4_digit(void)
{
	static char buffer[1024];

	strcpy(buffer, "[\"invoke\" , { \"id\" : \"1999\" ,\"args\":[]}]");
	
    TEST_ASSERT_EQUAL(1999, getIDToInvoke(buffer));
}

void finds_a_name_to_match(void)
{
	static char buffer[1024];

	strcpy(buffer, "[\"step_matches\",{\"name_to_match\":\"we're all wired\"}]");

	char *ptr = getNameToMatch(buffer);
    TEST_ASSERT_EQUAL_STRING("we're all wired", ptr);
}

void finds_a_name_to_match_irregular(void)
{
	static char buffer[1024];

	strcpy(buffer, "[\"step_matches\" , { \"name_to_match\" : \"we're all wired\"}]");

	char *ptr = getNameToMatch(buffer);
    TEST_ASSERT_EQUAL_STRING("we're all wired", ptr);
}

void handles_empty_invoke_request(void)
{
	static char buffer[1024];

	*buffer = 0;

    TEST_ASSERT_EQUAL(-1, getIDToInvoke(buffer));
}

void handles_empty_match_request(void)
{
	static char buffer[1024];

	*buffer = 0;
    TEST_ASSERT_EQUAL_STRING("", getNameToMatch(buffer));
}

