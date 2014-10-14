#ifndef __WIRE_LISTENER_H__
#define __WIRE_LISTENER_H__

typedef struct
{
    char *packet;
} ProtocolPacket;

int handleRequest(char *buffer, wire_context *context);
char *handle_callback(wire_feature_callback callback, wire_context *context);

#endif
