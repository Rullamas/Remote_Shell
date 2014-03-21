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
      To compile the project, use the command 'make'. This will make both the
      client executable and server executable.
	  
   
   USAGE:
      Proper usage for the client executable is "./client PORT IPADDRESS". An
      example of this is "./client 1234 127.0.0.1". Proper usage for the server
      executable is "./server PORT". An example of this is "./server 1234".
	  
	  
   RUNNING:
      To properly use the executables, first start the server with the above
      usage. The server will begin to listen and wait for commands. Then start
      the client which will ask for commands to be sent to the server. Once
      inputting an allowed command (date, ls, pwd, shutdown), the client will
      send the server the commands. Once the server processes the commands, the
      client will return the output of the server.
	  
   EXPLANATION:
      This project is a remote shell application using C which connects to a
	  server running on a remote host and then accesses its shell and commands.
	  To accomplish this, the project utilizes the Socket API. This is used to
	  set up a TCP connection as the Socket API has several functions that allow
	  for the connection to be set up such as socket(), bind(), listen(), connect(),
	  and accept(), all of which are nearly self explanatory and needed for the
	  three way handshake procedure that is needed to establish a TCP connection
	  between the two remote hosts. This is utilized through a client server
	  architecture meaning that the client (client.c) begins the communication
	  and the server (server.c) follows up to establish the connection.
	  
	  The basis of this connection establishment revolves around the three way
	  handshake of TCP. To explain, the "three way handshake" is the process of
	  transmitting three messages to negotiate and start a TCP session between
	  two hosts. This allows the two hosts to negotiate parameters before transmitting
	  any data. Using a three way handshake procedure also allows for the two
	  hosts to initiate and negotiate separate socket connections at the same time,
	  which is a requirement of this project. To complete the handshake process,
	  TCP does this using the Socket API functions. First, Host A (or the client)
	  sends a SYN packet to Host B (the server). Host B receives the SYN and
	  replies with a SYN-ACK. Host A receives the SYN-ACK sends an ACK in return.
	  Once Host B receives the ACK, the TCP socket connection is established.