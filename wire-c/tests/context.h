#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifdef ALLOC_CONTEXT
wire_context *context = 0;
#else
extern wire_context *context;
#endif

#endif
