#ifndef __WIRE_LISTENER_H__
#define __WIRE_LISTENER_H__

typedef struct
{
    char *packet;
} ProtocolPacket;

typedef int (*net_reader) (int socket, char *buffer);

int handleRequest(char *buffer, wire_context *context);
char *handle_callback(wire_feature_callback callback, wire_context *context);
int getRequest(net_reader reader, int socket, char *buffer, size_t len);

#endif
