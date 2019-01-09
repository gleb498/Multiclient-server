#include "connection_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "connection_list.h"

void *connection_handler(void *info) {

    check++; 
    int tmp = check;
    Data data = *(Data*)info;
    int rval;
    char *message = "message from server";
    char buffer[2000] = {0};
    while((rval = recv(data.socket, buffer, 2000, 0)) > 0){
    
        if(strcmp(buffer, "exit") == 0){
            removeNode(&data.head, data.socket);
            send(socket, message, strlen(message), 0);
        }

        printf("Message from %d: %s\n", tmp, buffer);
        send(data.socket, message, strlen(message), 0);
        memset(buffer, 0, 2000);
        usleep(1000000);

    }
}