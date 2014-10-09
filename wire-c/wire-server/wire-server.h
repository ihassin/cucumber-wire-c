//
//  wire-server.h
//  wire-server
//
//  Created by Itamar on 10/5/14.
//  Copyright (c) 2014 InContext. All rights reserved.
//
#ifndef __WIRE_SERVER_H__
#define __WIRE_SERVER_H__

typedef void (*wire_logger)(char *log);

typedef struct wire_context
{
	int port;
	wire_logger logger;
} wire_context;

int wire_server(wire_context *context);
int wire_listener(int port);
char *wire_version();

#endif
