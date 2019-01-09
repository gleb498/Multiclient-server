#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#define PORT 8082

char buffer[2000] = {0};
int sock = 0;
struct sockaddr_in serv_addr;
char *fun_client = "message from client";
char *toExit = "exit";


void handler(int signal){

    if(send(sock, toExit, strlen(toExit), 0) < 0){
        printf("Send ERROR\n");
        close(sock);
    }
    read(sock, buffer, 2048);
    printf("Final message from server: %s\n", buffer);
    exit(1);

}

int main() {

    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
        
    sock = socket(AF_INET, SOCK_STREAM,0);
    
    if(sock < 0){
        printf("Socket-client creation ERROR\n");
        exit(1);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("CONNECT ERROR\n");
        close(sock);
        exit(1);
    }

    while(1){

        if(send(sock, fun_client, strlen(fun_client), 0) < 0){
            printf("Send ERROR\n");
            close(sock);
            exit(1);
        }

        read(sock, buffer, 2048);
        printf("Client read: %s\n", buffer);
        usleep(1000000);

    }

    return 0;
}