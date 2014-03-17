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
 *   Creates a server through the Socket API which allows for commands
 *   to be received by the user. The server emulates a remote shell which
 *   returns to the user the ouput of commands such as date, ls, and pwd.
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

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{

	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	if (argc < 2)
	{
		fprintf(stderr,"server.c error: no port provided.\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		error("server.c error: could not open socket.");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		error("server.c error: binding error.");
	}

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0)
	{
		error("server.c error: socket acception error.");
	}

	bzero(buffer,256);

	n = read(newsockfd,buffer,255);

	if (n < 0)
	{
		error("server.c error: could not read from socket.");
	}

	printf("Here is the command: %s\n",buffer);

	n = write(newsockfd,"I got your command",18);

	if (n < 0)
	{
		error("server.c error: could not write to socket.");
	}
	return 0;
}