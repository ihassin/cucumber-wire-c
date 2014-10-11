#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __CONTEXT_H__
#include "context.h"
#endif

#ifndef __TCP_CLIENT_H__
#include "tcp_client.h"
#endif

#define BUF_SIZE 1024

#define LOG(m) { if (context->logger) (*context->logger) (m); }

int tcp_client(wire_context *context)
{
    char *address = "localhost";

    // descriptor number for the socket we'll use
    int serverSocket;

    // socket internet address data for the connection to the server
    struct sockaddr_in serverData;

    // host data
    struct hostent *host;

    // buffer for sending and receiving data
    char buffer[BUF_SIZE];
    int bytesReceived;
    char *packet;
    char *dejector;

    /* 
    * Set up the connection to a server 
    */

    bzero( &serverData, sizeof( serverData ) );
    // use the Internet Address Family (IPv4)
    serverData.sin_family = AF_INET;
    // get host data from the host address
    host = gethostbyname( address );
    // copy the address data from the host struct over to the server address struct
    bcopy( host->h_addr, &(serverData.sin_addr.s_addr), host->h_length);
    // set the port to connect to
    serverData.sin_port = htons(context->port);

    /* 
    * Open a TCP/IP socket to the server
    * (and save the descriptor so we can refer to it in the future)
    */
    serverSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );

    // connect to the server
    LOG("client: trying to connect")

    if ( connect( serverSocket, (struct sockaddr *)&serverData, sizeof( serverData ) ) < 0 ) {
        LOG("client: cannot connect")
        close( serverSocket );
        return(1);
    }

    if(context->packet_injector)
    {
        packet = (*context->packet_injector) ();
    }
    else
    {
        packet = "unknown injector";
    }
    strncpy(buffer, packet, strlen(packet));

    if(context->packet_dejector)
    {
        dejector = (*context->packet_dejector) ();
    }
    else
    {
        dejector = "unknown dejector";
    }

    LOG("client: sending packet")
    LOG(packet)

    if (send(serverSocket, buffer, strlen( buffer), 0) <= 0)
    {
        LOG("client: cannot send")
        close( serverSocket );
        return(1);
    }

    // wait to receive data from the server
    bytesReceived = recv( serverSocket, buffer, BUF_SIZE, 0 );
    if (bytesReceived <= 0)
    {
        LOG("client: cannot read")
        close( serverSocket );
        return(1);
    }
    // terminate the bytes as a string and print the result
    buffer[bytesReceived] = 0;
    if(context->logger)
    {
        LOG("client: got: ")
        LOG(buffer)
    }

    close(serverSocket);
    return(strcmp(buffer, dejector));
}
