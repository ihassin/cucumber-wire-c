//
//  wire-server.c
//  wire-server
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#define kVersion "0.0.0.0"

int wire_server(wire_context *context)
{
	if (context->port <= 0)
	{
		return(1);
	}
	if(context->logger)
	{
		(*context->logger) ("wire_server: Started");
	}

	if(context->logger)
	{
		(*context->logger) ("wire_server: Shut down");
	}
	return(0);
}
