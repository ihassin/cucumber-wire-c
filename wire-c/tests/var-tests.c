#include <string.h>

#ifndef __VAR_TESTS_H__
#include "var-tests.h"
#endif

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

void finds_gherkin_var(void)
{
	static char buffer[1024];

	strcpy(buffer, "this 'scenario' is run");
	
    TEST_ASSERT_EQUAL_STRING("scenario", getGherkinVar(buffer));
}

void does_not_find_gherkin_var_when_missing(void)
{
	static char buffer[1024];

	strcpy(buffer, "this scenario is run");
	
    TEST_ASSERT_EQUAL_STRING(0, getGherkinVar(buffer));
}

void does_not_find_gherkin_var_when_null(void)
{	
    TEST_ASSERT_EQUAL_STRING(0, getGherkinVar(0));
}

void does_not_find_gherkin_var_when_empty(void)
{	
    TEST_ASSERT_EQUAL_STRING(0, getGherkinVar(""));
}

void does_not_find_gherkin_var_when_in_double_quotes(void)
{	
	static char buffer[1024];

	strcpy(buffer, "this \"scenario\" is run");
	
    TEST_ASSERT_EQUAL_STRING(0, getGherkinVar(buffer));
}

// ["invoke",{"id":"3","args":["scenario"]}]
void finds_json_arg(void)
{
	static char buffer[1024];

	strcpy(buffer, "[\"invoke\",{\"id\":\"3\",\"args\":[\"scenario\"]}]");
	
    TEST_ASSERT_EQUAL_STRING("scenario", getJSONArg(buffer));
}
