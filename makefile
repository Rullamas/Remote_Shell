#------------------------------------------------------------------------------
#  Makefile for CMPE 150 Project
#
#  make                     makes Client and Server
#------------------------------------------------------------------------------

BASE_SOURCES   = Client.c Server.c
BASE_OBJECTS   = Client.o Server.o
HEADERS        = Client.h Server.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Client : Client.o $(BASE_OBJECTS)
	$(LINK) Client Client.o $(BASE_OBJECTS)

Server : Server.o $(BASE_OBJECTS)
	$(LINK) Server Server.o $(BASE_OBJECTS)

Client.o : Client.c $(HEADERS)
	$(COMPILE) Client.c

Server.o : Server.c $(HEADERS)
	$(COMPILE) Server.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Client Server Client.o Server.o $(BASE_OBJECTS)
