#------------------------------------------------------------------------------
#  Makefile for CMPE 150 Project
#
#  make                     makes client and server
#------------------------------------------------------------------------------

BASE_SOURCES   = client.c server.c
BASE_OBJECTS   = client.o server.o
#HEADERS        = client.h server.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

client : client.o 
	$(LINK) client client.o 

server : server.o 
	$(LINK) server server.o 

client.o : client.c 
	$(COMPILE) client.c

server.o : server.c 
	$(COMPILE) server.c

$(BASE_OBJECTS) : $(BASE_SOURCES)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) client server client.o server.o $(BASE_OBJECTS)
