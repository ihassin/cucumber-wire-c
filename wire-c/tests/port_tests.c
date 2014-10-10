#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#include <pthread.h>
#include <assert.h>

#ifndef __PORT_TESTS_H__
#include "port_tests.h"
#endif

int dummy_listener(int port, wire_logger logger)
{
    (*logger) ("Dummy listener called\n");
    return(0);
}

void accepts_valid_port_number(void)
{
	context->listener = dummy_listener;
    TEST_ASSERT_EQUAL(0, wire_server(context));
}

void rejects_negative_port_number(void)
{
	context->port = -3901;
    TEST_ASSERT_EQUAL(1, wire_server(context));
}

void rejects_zero_port_number(void)
{
	context->port = 0;
    TEST_ASSERT_EQUAL(1, wire_server(context));
}

void *thread_routine(void *data)
{
    wire_context *context = (wire_context *) data;
    int ret_val = (*context->listener) (context->port, context->logger);
    return(0);
}

int tcp_client(wire_context *context);

void listens_on_requested_port(void)
{
	context->port = 3901;
    context->listener = wire_listener_default;

    // Create the thread using POSIX routines.
    pthread_attr_t  attr;
    pthread_t       posixThreadID;
    int             returnVal;
 
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    assert(!returnVal);
 
    int threadError = pthread_create(&posixThreadID, &attr, &thread_routine, context);
 
    returnVal = pthread_attr_destroy(&attr);
    assert(!returnVal);
    if (threadError != 0)
    {
         // Report an error.
    }

    int ret_val = tcp_client(context);
    TEST_ASSERT_EQUAL(0, ret_val);
}

#define BUF_SIZE 1024

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
    if(context->logger)
    {
        (*context->logger) ("client: trying to connect\n");
    }
    if ( connect( serverSocket, (struct sockaddr *)&serverData, sizeof( serverData ) ) < 0 ) {
        if(context->logger)
        {
            (*context->logger) ("client: cannot connect\n");
        }
        close( serverSocket );
        return(1);
    }

    strncpy( buffer, "Hi", 3 );

    if(context->logger)
    {
        (*context->logger) ("client: sending packet\n");
    }
    send( serverSocket, buffer, strlen( buffer ), 0 );

    // wait to receive data from the server
    bytesReceived = recv( serverSocket, buffer, BUF_SIZE, 0 );

    // terminate the bytes as a string and print the result
    buffer[bytesReceived]= '\0';
    if(context->logger)
    {
        (*context->logger) ("client: got: ");
        (*context->logger) (buffer);
    }

    close( serverSocket );

    return 0;
}

