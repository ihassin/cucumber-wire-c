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
	int ret_val = 0;

	if (context->port <= 0)
	{
		return(1);
	}

	if(context->logger)
	{
		(*context->logger) ("wire_server: Started\n");
	}

	ret_val = (*context->listener) (context->port, context->logger, context->single_scenario);

	if(context->logger)
	{
		(*context->logger) ("wire_server: Shut down\n");
	}
	return(ret_val);
}

char *wire_version()
{
	return(kVersion);
}
