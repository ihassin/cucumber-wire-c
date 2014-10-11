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
#define kStepMatch      "[\"step_matches\""
#define kSnippet        "[\"snippet_text\""

static ProtocolPacket protocolPackets[] = {
    kBeginScenario, 
    kEndScenario,
    kStepMatch,
    kSnippet
};

int wire_listener_default(int port, wire_logger logger, int loops)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int n, ret_val;

    LOG("listener: Allocating socket")

    /* First call to socket() function */
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
      	LOG("ERROR opening socket")
        return(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
 
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    LOG("listener: Binding socket")
    ret_val = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret_val < 0)
    {
        LOG("listener: Cannot bind")
        printf("cannot bind: %d errno:%d\n", ret_val, errno);
        return(2);
    }

    LOG("listener: Listening on socket")
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
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
    {
        close(newsockfd);
        close(sockfd);
        LOG("ERROR on accept")
        return(4);
    }
    LOG("listener: Reading data")

    while(loops--)
    {
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
        char *closing = strstr(buffer, "\n");
        if (closing)
        {
            *(closing) = 0;
        }
        if(!*buffer)
        {
            loops++;
            continue;
        }

        LOG(buffer)

        int found;
        int arrayLen = sizeof(protocolPackets)/sizeof(ProtocolPacket);

        for(found = 0; found < arrayLen; found++)
        {
            char *packet = protocolPackets[found].packet;
            if(strstr(buffer, packet))
            {
                break;
            }
        }
        if(found < arrayLen)
        {
            strcpy(buffer, "[\"success\", []]\n");
        }
        else
        {
            strcpy(buffer, "[\"fail\"]\n");
        }
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
    }
    LOG("listener: Closing socket")

    close(newsockfd);
    close(sockfd);
    return 0; 
}
