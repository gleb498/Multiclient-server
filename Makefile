CC=gcc
CFLAGS=-c -Wall

server: server.o connection_handler.o connection_list.o
	$(CC) server.o connection_handler.o connection_list.o -lpthread -g -o $@

client: client.o
	$(CC) client.o -lpthread -g -o $@

server.o: server.c 
	$(CC) $(CFLAGS) server.c -g

client.o: client.c
	$(CC) $(CFLAGS) client.c -g

connection_handler.o: connection_handler.c
	$(CC) $(CFLAGS) connection_handler.c -g 

connection_list.o: connection_list.c	
	$(CC) $(CFLAGS) connection_list.c -g

clean:
	rm -f *.o server client