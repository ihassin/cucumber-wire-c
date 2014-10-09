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
    int n;

    if (logger)
    {
        (*logger) ("Allocating socket\n");
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

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
 
    if (logger)
    {
        (*logger) ("Binding socket\n");
    }
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
         //perror("ERROR on binding");
        return(2);
    }

    if (logger)
    {
        (*logger) ("Listening on socket\n");
    }
    /* Now start listening for the clients, here process will
    * go in sleep mode and will wait for the incoming connection
    */
    int ret_val = listen(sockfd, 5);
    if (ret_val < 0)
    {
        close(newsockfd);
        //perror("ERROR reading from socket");
        return(3);
    }
    clilen = sizeof(cli_addr);

    if (logger)
    {
        (*logger) ("Accepting connection\n");
    }
    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) 
    {
        close(newsockfd);
        //perror("ERROR on accept");
        return(4);
    }
    if (logger)
    {
        (*logger) ("Reading data\n");
    }
    /* If connection is established then start communicating */
    bzero(buffer, sizeof(buffer));
    n = read( newsockfd,buffer, sizeof(buffer)-1 );
    if (n < 0)
    {
        close(newsockfd);
        //perror("ERROR reading from socket");
        return(5);
    }
    buffer[n] = 0;
    printf("Here is the message: %s\n", buffer);

    if (logger)
    {
        (*logger) ("Writing response\n");
    }
    /* Write a response to the client */
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
    {
        close(newsockfd);
        //perror("ERROR writing to socket");
        return(6);
    }
    if (logger)
    {
        (*logger) ("Closing socket\n");
    }
    close(newsockfd);
    return 0; 
}
