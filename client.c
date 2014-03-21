/* CMPE 150 Final Project
 * ======================
 * 
 * Brandon Rullamas, brullama@ucsc.edu
 * Erik Swedberg, eswedber@ucsc.edu
 *
 * NAME
 *   client.c
 *
 * DESCRIPTION
 *   Creates a client through the Socket API which allows for the user
 *   to send the server (made through server.c) commands. client.c will
 *   then return the output of the server.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <time.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

#define MAX_LEN 512

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[MAX_LEN];
    char command[MAX_LEN];

    if (argc < 3) {
        fprintf(stderr,"Usage: %s PORT IPADDRESS\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[1]);

    // creation of socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error("client.c error: could not open socket.");
    }

    server = gethostbyname(argv[2]);
    if (server == NULL) {
        fprintf(stderr, "client.c error: no such host.\n");
        exit(0);
    }

    // more establishment of socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,
       server->h_length);

    serv_addr.sin_port = htons(portno);


    if (connect(sockfd,(struct sockaddr*) &serv_addr,
       sizeof(serv_addr)) < 0) {
        error("client.c error: could not connect.");
    }
    
    while(1) {
        printf("Please enter a command: ");
        bzero(command,MAX_LEN);
        fgets(command,MAX_LEN,stdin);
        n = write(sockfd,command,strlen(command));
        if (n < 0) {
            error("client.c error: could not write to socket.");
        }
        
        // empty out buffer before reading in more data
        bzero(buffer,MAX_LEN);
        n = read(sockfd, buffer, MAX_LEN);
        printf("%s\n",buffer);

        
        if (n < 0) {
            error("client.c error: could not read socket.");
        }
        
        if(strcmp(buffer,"Shutting down") == 0) {
            return 0;
        }
    }

    return 0;
}
