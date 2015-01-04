#ifndef __HANDLE_REQUEST_TESTS_H__
#define __HANDLE_REQUEST_TESTS_H__

#ifndef __CONTEXT_H__
#include "context.h"
#endif

#ifndef __WIRE_LISTENER_H__
#include "wire-listener.h"
#endif

void rejects_null_context(void);
void rejects_null_buffer(void);
void rejects_empty_buffer(void);
void returns_fail_for_unknown_request(void);
void returns_success_for_known_request(void);
void returns_success_without_begin_callback(void);
void returns_success_without_end_callback(void);
void returns_success_with_begin_callback(void);
void returns_success_with_end_callback(void);
void returns_fail_with_neg_begin_callback(void);
void returns_fail_with_neg_end_callback(void);
void handle_callback_null_context(void);
void handle_step_match_no_params(void);
void handle_invoke_underscript(void);
void handle_invoke_overscript(void);
void handle_invoke_rightscript(void);

#endif

