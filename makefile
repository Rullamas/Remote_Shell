#------------------------------------------------------------------------------
#  Makefile for CMPE 150 Project
#
#  make client              makes client
#  make server              makes server
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

$(BASE_OBJECTS) : $(BASE_SOURCES)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) client server client.o server.o $(BASE_OBJECTS)
