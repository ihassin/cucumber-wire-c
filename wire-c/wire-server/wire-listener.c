#ifndef __SYSTEM_INCLUDES_H__
#include "system-includes.h"
#endif

#ifndef __WIRE_SERVER_H__
#include "wire-server.h"
#endif

int wire_listener_default(int port, wire_logger logger)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, ret_val;

    if (logger)
    {
        (*logger) ("listener: Allocating socket");
    }
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
      	//perror("ERROR opening socket");
        return(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
 
    if (logger)
    {
        (*logger) ("listener: Binding socket");
    }
    /* Now bind the host address using bind() call.*/
    ret_val = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret_val < 0)
    {
        if (logger)
        {
            (*logger) ("listener: Cannot bind");
        }
        printf("cannot bind: %d\n", ret_val);
        return(2);
    }

    if (logger)
    {
        (*logger) ("listener: Listening on socket");
    }
    /* Now start listening for the clients, here process will
    * go in sleep mode and will wait for the incoming connection
    */
    ret_val = listen(sockfd, 5);
    if (ret_val < 0)
    {
        close(sockfd);
        //perror("ERROR reading from socket");
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
        //perror("ERROR on accept");
        return(4);
    }
    if (logger)
    {
        (*logger) ("listener: Reading data");
    }
    /* If connection is established then start communicating */
    bzero(buffer, sizeof(buffer));
    n = read( newsockfd,buffer, sizeof(buffer) - 1 );
    if (n < 0)
    {
        close(newsockfd);
        close(sockfd);
        return(5);
    }
    buffer[n] = 0;
    if (logger)
    {
        (*logger) ("listener: Read: ");
        (*logger) (buffer);
    }

    if (logger)
    {
        (*logger) ("listener: Writing response");
    }
    /* Write a response to the client */
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
    {
        close(newsockfd);
        close(sockfd);
        return(6);
    }
    if (logger)
    {
        (*logger) ("listener: Closing socket");
    }
    close(newsockfd);
    close(sockfd);
    return 0; 
}
