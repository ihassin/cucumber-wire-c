//
//  wire-server.h
//  wire-server
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#ifndef __WIRE_SERVER_H__
#define __WIRE_SERVER_H__

struct wire_context;

typedef void (*wire_logger) (char *log);
typedef int (*wire_listener) (struct wire_context *context);
typedef char *(*wire_packet_injector) (struct wire_context *context);
typedef int (*wire_feature_callback) (struct wire_context *context);
typedef int (*wire_step_match_callback) (struct wire_context *context);
typedef int (*wire_invoke_callback) (struct wire_context *context);

typedef struct step_match {
	char name_to_match[1024];
} StepMatch;

typedef struct step_invoke {
	int id;
} StepInvoke;

typedef struct wire_context
{
	int port;
	int single_scenario;
	wire_logger 				logger;
	wire_listener 				listener;
	wire_packet_injector 		packet_injector;
	wire_packet_injector 		packet_dejector;
	wire_feature_callback		begin_callback;
	wire_feature_callback		end_callback;
	wire_step_match_callback	step_match_callback;
	wire_invoke_callback		invoke_callback;
	char incoming[1024];
	char outgoing[1024];
	union
	{
		StepMatch step_match;
		StepInvoke step_invoke;
	} request_block;
} wire_context;

int wire_server(wire_context *context);
int wire_listener_default(wire_context *context);
char *wire_version(void);

#endif
