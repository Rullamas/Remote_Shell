/* CMPE 150 Final Project
 * ======================
 * 
 * Brandon Rullamas, brullama@ucsc.edu
 * Erik Swedberg, eswedber@ucsc.edu
 *
 * NAME
 *   server.c
 *
 * DESCRIPTION
 *   Creates a server through the Socket API which 
 *   allows for commands to be received by the user. 
 *   The server emulates a remote shell which returns
 *   to the user the ouput of commands such as date, ls, 
 *   and pwd.
 */
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 512

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char * argv[]) {

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[MAX_LEN];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char line[MAX_LEN];
    int badpacket = 0;
    int endofsession = 0;

    if (argc < 2) {
        fprintf(stderr,"server.c error: no port provided.\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error("server.c error: could not open socket.");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    // establishment of buffer
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
       sizeof(serv_addr)) < 0) {
        error("server.c error: binding error.");
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    // infinite loop to allow for multiple commands
    while(1) {

        // accepts a new socket
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,
           &clilen);

        if (newsockfd < 0) {
            error("server.c error: socket acception error.");
        }

        bzero(buffer,MAX_LEN);
        
        // every new client starts with new session flag
        endofsession = 0;
        while(!endofsession) {
            n = read(newsockfd,buffer,MAX_LEN);
            
            if (n < 0) {
                error("server.c error: could not read from socket.");
            } else if ( n == 0) {
                endofsession = 1;
                error("server.c error: client left.");
            }

            // assume packet will be good
            badpacket = 0;
            if (strcmp("ls\n", buffer) == 0) {
                system("ls > n");
                printf("did ls\n");
            } else if (strcmp("date\n", buffer) == 0) {
                system("date > n");
                printf("did date\n");
            } else if (strcmp("pwd\n", buffer) == 0) {
                system("pwd > n");
                printf("did pwd\n");
            } else if (strcmp("shutdown\n", buffer) == 0) {
                printf("Shutdown, end session\n");
                n = write(newsockfd,"Shutting down",13);
                endofsession = 1;
            } else if (strcmp("^C", buffer) == 0) {
                endofsession = 1;
            } else {   
                n = write(newsockfd,"Invalid Command",15);
                badpacket = 1;
            }
    
            FILE *out = fopen("n", "r");
            bzero(buffer,MAX_LEN);
            if(!badpacket) {
                if(out != NULL) {
                    while (fgets(line, MAX_LEN, out) != NULL) {
                        
                        // allows for only one buffer to be sent
                        strcat(buffer, line);
                        
                        // comment below allows for tracking of line
                        // sizes of each command
                        //printf("linesize: %d\n", (int)strlen(line));
                    }
                    
                    n = write(newsockfd, buffer, (int)strlen(buffer));
                    bzero(line, MAX_LEN);
                    bzero(buffer, MAX_LEN);
                    
                    fclose(out);
                }
            }
            if(!endofsession && !badpacket) system("rm n");
                    
            if (n < 0) {
                error("server.c error: could not write to socket.");
            }
        }
        
        printf("Ended session with Client\n");
    }
        
    return 0;
}
