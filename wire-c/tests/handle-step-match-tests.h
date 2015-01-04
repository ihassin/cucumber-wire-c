#ifndef __HANDLE_STEP_MATCH_TESTS_H__
#define __HANDLE_STEP_MATCH_TESTS_H__

#ifndef __CONTEXT_H__
#include "context.h"
#endif

#ifndef __WIRE_LISTENER_H__
#include "wire-listener.h"
#endif

void handle_step_match_no_params(void);
void step_match_callback_no_call_with_no_buffer(void);
void step_match_callback_no_call_with_null_buffer(void);
void handle_step_match_not_found(void);

#endif
