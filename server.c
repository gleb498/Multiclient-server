#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <pthread.h>
#include "connection_handler.h"
#include "connection_list.h"

int new_socket, rval, sock_fd, pid;
struct sockaddr_in address;
const int PORT = 8082;
connection_info* head = NULL;

void handler(int signal){

    removeList(&head);
    close(sock_fd);
    exit(1);

}

int main() {

    signal(SIGINT, handler);
    signal(SIGTSTP, handler); 
    Data data;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd < 0){

        printf("Socket-server creation ERROR\n");
        exit(1);

    }

    int enable = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){

        printf("FAIL\n");

    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htons(INADDR_ANY);
    address.sin_port = htons(PORT);

    if(bind(sock_fd,(struct sockaddr*)&address, sizeof(address))){

        printf("Bind ERROR\n");
        exit(1);

    } 
    
    listen(sock_fd, 1);
    while((new_socket = accept(sock_fd, (struct sockaddr*) NULL, NULL))){

        data.socket = new_socket;
        data.head = NULL;
        push(&head, &data); 

    }


    return 0;
  }