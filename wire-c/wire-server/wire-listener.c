#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifndef __WIRE_LISTENER_H__
#include "wire-listener.h"
#endif

#define LOG(m) { if (logger) (*logger) (m); }

#define kBeginScenario  "[\"begin_scenario\"]"
#define kEndScenario    "[\"end_scenario\"]"

static ProtocolPacket protocolPackets[] = {
    kBeginScenario, 
    kEndScenario
};

int wire_listener_default(int port, wire_logger logger)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, ret_val;

    LOG("listener: Allocating socket")

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
      	LOG("ERROR opening socket")
        return(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
 
    LOG("listener: Binding socket")

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    /* Now bind the host address using bind() call.*/
    ret_val = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret_val < 0)
    {
        LOG("listener: Cannot bind")
        printf("cannot bind: %d errno:%d\n", ret_val, errno);
        return(2);
    }

    LOG("listener: Listening on socket")

    /* Now start listening for the clients, here process will
    * go in sleep mode and will wait for the incoming connection
    */
    ret_val = listen(sockfd, 5);
    if (ret_val < 0)
    {
        close(sockfd);
        LOG("ERROR reading from socket")
        return(3);
    }
    clilen = sizeof(cli_addr);

    if (logger)
    {
        (*logger) ("listener: Accepting connection");
    }
    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) 
    {
        close(newsockfd);
        close(sockfd);
        LOG("ERROR on accept")
        return(4);
    }
    LOG("listener: Reading data")

    /* If connection is established then start communicating */
    bzero(buffer, sizeof(buffer));
    n = read(newsockfd,buffer, sizeof(buffer) - 1);
    if (n < 0)
    {
        LOG("ERROR on read")
        close(newsockfd);
        close(sockfd);
        return(5);
    }
    buffer[n] = 0;
    LOG("listener: read: ")
    LOG(buffer)

    // Process token here
    int found;
    int arrayLen = sizeof(protocolPackets)/sizeof(ProtocolPacket);
    char *closing = strstr(buffer, "]");
    if (closing)
    {
        *(closing + 1) = 0;
    }
    for(found = 0; found < arrayLen; found++)
    {
        char *packet = protocolPackets[found].packet;
        if(strcmp(buffer, packet) == 0)
        {
            break;
        }
    }
    if(found < arrayLen)
    {
        strcpy(buffer, "[\"success\"]");
    }
    else
    {
        strcpy(buffer, "[\"fail\"]");
    }
    LOG("listener: Writing response")
    LOG(buffer)

    /* Write a response to the client */
    int len = strlen(buffer);
    n = write(newsockfd, buffer, len);
    if (n != len)
    {
        LOG("ERROR on write")
        close(newsockfd);
        close(sockfd);
        return(6);
    }
    LOG("listener: Closing socket")

    close(newsockfd);
    close(sockfd);
    return 0; 
}
