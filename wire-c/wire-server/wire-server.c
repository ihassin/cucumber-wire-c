//
//  wire-server.c
//  wire-server
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#include <stdlib.h>
#include <string.h>

#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif


/// callbacks


#ifndef __API_H__
#include "api.h"
#endif

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

void my_logger(char *log)
{
    printf("Logger: %s\n", log);
}

int begin_callback(struct wire_context *context)
{
    return(0);
}

int end_callback(struct wire_context *context)
{
    return(0);
}

int step_match_callback(wire_context *context)
{
    char *name_to_match = context->request_block.step_match.name_to_match;
    int retVal = api_match_name(name_to_match);
    
    if (retVal == -1)
    {
        sprintf(context->outgoing, "[\"success\", []]\n");
    }
    else
    {
        char *var = getGherkinVar(name_to_match);
        static char buff[1024];
        if(var)
        {
            sprintf(buff, "{\"val\":\"%s\", \"pos\":%d}", var, getGherkinVarPosition(name_to_match, var));
        }
        sprintf(context->outgoing, "[\"success\",[{\"id\":\"%d\", \"args\":[%s]}]]\n", retVal, buff);
    }
    return(0);
}

int step_snippet_callback(wire_context *context)
{
    int retVal = api_match_name(context->request_block.step_match.name_to_match);
    
    if (retVal == -1)
    {
        sprintf(context->outgoing, "[\"success\", []]\n");
    }
    else
    {
        sprintf(context->outgoing, "[\"success\",[\"int %s(void) { return %d; } \"]]\n", context->request_block.step_match.name_to_match, retVal);
    }
    return(0);
}

int invoke_callback(wire_context *context)
{
    if(context->logger)
    {
        char buffer[100];
        sprintf(buffer, "Invoking %d\n", context->request_block.step_invoke.id);
        (*context->logger) (buffer);
    }
    
    return(invoke_by_id(context->request_block.step_invoke.id, (void *) context));
}



#define kVersion "0.0.0.0"

int wire_server(wire_context *context)
{
	int retVal = 0;

	if (context->port <= 0)
	{
		return(1);
	}

	if(context->logger)
	{
		(*context->logger) ("wire_server: Started\n");
	}

	retVal = (*context->listener) (context);

	if(context->logger)
	{
		(*context->logger) ("wire_server: Shut down\n");
	}
	return(retVal);
}

int run_server(int argc, char **argv)
{
    int retVal;
    wire_context *context;
    
    context = malloc(sizeof(wire_context));
    memset(context, 0, sizeof(wire_context));
    

    context->port 					= 3901;
    context->single_scenario 		= 1;
    context->logger 				= my_logger;

//    context->port 					= atoi(argv[1]);
//    context->single_scenario 		= atoi(argv[2]);
//    context->logger 				= atoi(argv[3]) == 1 ? my_logger : 0;
    context->begin_callback 		= begin_callback;
    context->end_callback 			= end_callback;
    context->listener 				= (wire_listener) wire_listener_default;
    context->step_match_callback 	= step_match_callback;
    context->invoke_callback 		= invoke_callback;
    context->step_snippet_callback 	= step_snippet_callback;
    
    retVal = wire_server(context);
    return(retVal);
}

char *wire_version()
{
	return(kVersion);
}



