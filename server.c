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
	exit(0);
}

int main(int argc, char *argv[])
{
	int sock, length, fromlen, n;
	time_t mytime;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[1024];
	char cwd[1024];

	if (argc < 2)
	{
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		error("Opening socket");
	}
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));
	if (bind(sock,(struct sockaddr *)&server,length)<0)
	{
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);
	while (1)
	{
		n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
		if (n < 0)
		{
			error("recvfrom");
		}
		write(1,"Received a datagram: ",21);
		write(1,buf,n);
		
		if(strcmp(buf,"date")){
			
		}else if(strcmp(buf,"date")){
			
		}else if(strcmp(buf,"date")){
			
		}else if(strcmp(buf,"date")){
			
		}else{
			error("bad command");
		}
			case "date": 
				mytime = time(NULL);
				//send ctime(&mytime)
			break;
			case "ls": 
				//I think this is what we want, plus a few of the corrections in the comments
				//http://stackoverflow.com/questions/2985224/how-to-implement-unix-ls-s-command-in-c
			
			break;
			case "pwd": 
				//something like this
       				if (getcwd(cwd, sizeof(cwd)) != NULL)
           				fprintf(stdout, "Current working dir: %s\n", cwd);
      	 			else
           				perror("getcwd() error");
			
			break;
			case "shutdown": 
				n = sendto(sock,"Received a message\n",17,
				0,(struct sockaddr *)&from,fromlen);
				return 0;
			break;
			default:
				error("no command");
			break;
		}
		
		n = sendto(sock,"Received a message\n",17,
				0,(struct sockaddr *)&from,fromlen);
		if (n < 0)
		{
			error("sendto");
		}
	}
}
