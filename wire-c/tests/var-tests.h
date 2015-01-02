#ifndef __VAR_TESTS_H__
#define __VAR_TESTS_H__

#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void finds_gherkin_var(void);
void does_not_find_gherkin_var_when_missing(void);
void does_not_find_gherkin_var_when_null(void);
void does_not_find_gherkin_var_when_empty(void);
void does_not_find_gherkin_var_when_in_double_quotes(void);
void finds_json_arg(void);

#endif

