CMPE 150 Project
================

Winter '14
Brandon Rullamas, brullama@ucsc.edu
Erik Swedberg, eswedber@ucsc.edu

   CONTAINS:
      client.c
      server.c
      makefile
      README.txt
	  
      client.c:
         Creates a client through the Socket API which allows for the user
         to send the server (made through server.c) commands. client.c will
         then return the output of the server.
	  
      server.c:
         Creates a server through the Socket API which allows for commands
         to be received by the user. The server emulates a remote shell which
         returns to the user the ouput of commands such as date, ls, and pwd.
	  
      makefile:
         Compiles client.c and server.c into executables.
		 
      README.txt:
         Explanation of the project.
		 
   
   COMPILING:
      To compile the project, use the command "make". This will make both the
      client executable and server executable.
      
      To compile individually, type "make server" or "make client"
	  
   
   USAGE:
      Proper usage for the client executable is "./client PORT IPADDRESS". 
      Proper usage for the server executable is "./server PORT". 
      
      An example of these is "./server 1234" and "./client 1234 128.114.104.230".
	  
	  
   RUNNING:
      To properly use the executables, first start the server with the above
      usage. The server will begin to listen and wait for commands. Then start
      the client which will ask for commands to be sent to the server. Once
      inputting an allowed command (date, ls, pwd, shutdown), the client will
      send the server the commands. Once the server processes the commands, the
      client will return the output of the server.