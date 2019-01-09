#include <stdlib.h>
#include <pthread.h>

typedef struct node{
    int clientId;
    int socket_desc;
    pthread_t thread_desc;
    struct node* next;
    struct node* prev;
} connection_info;

typedef struct data{
    int socket;
    connection_info* head;
} Data;

static int clientId = 0;

void push(connection_info**, Data*);
void removeList(connection_info**);
void removeNode(connection_info**, int);
void getHead();
