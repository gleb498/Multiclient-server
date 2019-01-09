#include "connection_list.h"
#include "connection_handler.h"


void push(connection_info** head, Data* data) {

    if ((*head) != NULL){

        connection_info* current = (*head);

        while (current->next != NULL) {
            current = current->next;
        }

        data->head = *head;

        current->next = malloc(sizeof(connection_info));
        clientId++;
        current->next->clientId = clientId;
        current->next->prev = current; 
        current->next->socket_desc = data->socket;
        pthread_create(&(current->next->thread_desc), NULL, connection_handler, (void*) &(*data));
        current->next->next = NULL;

    } else {

        (*head) = malloc(sizeof(connection_info));
        data->head = *head;
        clientId++;
        (*head)->clientId = clientId;
        (*head)->next = NULL; 
        (*head)->prev = NULL;
        (*head)->socket_desc = data->socket;
        pthread_create(&((*head)->thread_desc), NULL, connection_handler, (void*) &(*data));
    }
}

void removeNode(connection_info** head, int sock) {

    connection_info* current = (*head);
    
    while (current->socket_desc != sock) {
        current = current->next;
    }

    if(current->socket_desc != sock){
        printf("Can't find socket!\n");
    } else {
        printf("Socket was found!\n");
    }
    connection_info *prev, *next;
    prev = current->prev;
    next = current->next;
    if(prev){
        prev->next = current->next;
    }
    if(next){
        next->prev = current->prev;
    }
    close(current->socket_desc);
    close(current->thread_desc);
    free(current);
    printf("Client under socket %d was deleted!\n", sock);
}

void removeList(connection_info** head){

    if((*head) != NULL){

        connection_info* current = (*head);
        connection_info* nextNode = NULL;

        while(current){

            nextNode = current->next;
            printf("Client %d under socket %d was deleted!\n", current->clientId, current->socket_desc);
            close(current->socket_desc);
            free(current);
            current = nextNode;

        }

    }
}
