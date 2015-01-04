#ifndef __TEST_CONTEXT_H__
#define __TEST_CONTEXT_H__

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifdef ALLOC_CONTEXT
struct wire_context *context = 0;
#else
extern struct wire_context *context;
#endif

#endif
