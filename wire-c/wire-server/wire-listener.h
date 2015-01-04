#ifndef __WIRE_LISTENER_H__
#define __WIRE_LISTENER_H__

#ifndef __TOKEN_HANDLING_H__
#include "token-handling.h"
#endif

#ifndef __CONTEXT_H__
#include "context.h"
#endif

typedef struct
{
    char *packet;
} ProtocolPacket;

typedef int (*net_reader) (int socket, char *buffer);

int handleRequest(char *buffer, struct wire_context *context);
char *handle_callback(wire_feature_callback callback, struct wire_context *context);
int getRequest(net_reader reader, int socket, char *buffer, size_t len);

int getNetworkByte(int socket, char *buffer);
void cleanup(int socket1, int socket2);
int acceptConnection(int sockfd);
int makeSocket(int port);

#define LOG(m) { if (context->logger && m) (*context->logger) (m); }

#endif
