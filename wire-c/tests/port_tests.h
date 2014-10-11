#ifndef __PORT_TESTS_H__
#define __PORT_TESTS_H__

#ifndef __CONTEXT_H__
#include "context.h"
#endif

void accepts_valid_port_number(void);
void rejects_negative_port_number(void);
void rejects_zero_port_number(void);
void listens_on_requested_port(void);

#endif
