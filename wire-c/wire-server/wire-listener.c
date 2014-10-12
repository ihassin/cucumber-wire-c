#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

#ifndef __WIRE_LISTENER_H__
#include "wire-listener.h"
#endif

#define LOG(m) { if (context->logger && m) (*context->logger) (m); }

#define kBeginScenario  "[\"begin_scenario\"]"
#define kEndScenario    "[\"end_scenario\"]"
#define kStepMatch      "[\"step_matches\""
#define kSnippet        "[\"snippet_text\""
#define kInvoke         "[\"invoke\""

static ProtocolPacket protocolPackets[] = {
    kBeginScenario, 
    kEndScenario,
    kStepMatch,
    kSnippet,
    kInvoke
};

int getRequest(int socket, char *buffer, size_t len)
{
    bzero(buffer, len);

    int count = len;
    int rc;

    while(count > 0)
    {
        rc = recv(socket, buffer, 1, 0);
        if (rc < 0)
        {
            return(-1);
        }
        if(rc == 0)
        {
            len -= count;
            break;
        }
        if(rc == 0 || *buffer == '\n')
        {
            *buffer = 0;
            len -= count;
            break;
        }
        buffer += rc;
        count -= rc;
    }
    return(len);
}

char *handle_callback(wire_feature_callback callback, wire_context *context)
{
    if(callback && ((*callback) (context) != 0))
    {
        return "[\"fail\",{\"message\":\"handler failed\"}]\n";
    }
    return "[\"success\"]\n";
}

int handleRequest(char *buffer, wire_context *context)
{
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
        switch(found)
        {
            case 0:                 // begin_scenario
                strcpy(buffer, handle_callback(context->begin_callback, context));
                break;

            case 1:                 // end_scenario
                strcpy(buffer, handle_callback(context->end_callback, context));
                break;

            case 2:
                strcpy(buffer, "[\"success\",[{\"id\":\"1\", \"args\":[]}]]\n");
                break;

            default:
                strcpy(buffer, "[\"success\", []]\n");
                break;                
        }
    }
    else
    {
        strcpy(buffer, "[\"fail\",{\"message\":\"Cucumber sent us an unknown command\"}]\n");
    }
    LOG(buffer)
    return(0);
}

void cleanup(int socket1, int socket2)
{
    close(socket1);
    close(socket2);
}

int acceptConnection(int sockfd)
{
    struct sockaddr_in cli_addr;

    socklen_t clilen = sizeof(cli_addr);
    return accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
}

int wire_listener_default(wire_context *context)
{
    int sockfd, newsockfd;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    int n, ret_val;

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
    serv_addr.sin_port = htons(context->port);
 
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

    newsockfd = acceptConnection(sockfd);
    if (newsockfd < 0) 
    {
        cleanup(newsockfd, sockfd);
        LOG("ERROR on accept")
        return(4);
    }

    while(1)
    {
        ret_val = getRequest(newsockfd, buffer, sizeof(buffer));
        if (ret_val <= 0)
        {
            close(newsockfd);
            if(context->single_scenario)
            {
                break;
            }
            newsockfd = acceptConnection(sockfd);
            if (newsockfd < 0) 
            {
                cleanup(newsockfd, sockfd);
                LOG("ERROR on accept-2")
                return(5);
            }
            continue;
        }
        LOG(buffer)

        handleRequest(buffer, context);

        /* Write a response to the client */
        int len = strlen(buffer);
        n = send(newsockfd, buffer, len, 0);
        if (n != len)
        {
            cleanup(newsockfd, sockfd);
            LOG ("ERROR on write")
            return(6);
        }
    }
    cleanup(newsockfd, sockfd);
    return 0; 
}
