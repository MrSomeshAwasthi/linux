/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
void* read_input(void* client_socket)
{
    char read_buf[1024];
    int client_sock = *((int*)client_socket);
    while (1) {
        memset(read_buf, 0, 1024);
        int bytesRead = recv(client_sock,read_buf,1024,0);
        // printf("read, %d\n",bytesRead);
        if (bytesRead == -1)
        {
            perror("Error reading data from server");
            break;
        }

        if (bytesRead == 0)
        {
            printf("Server closed the connection.\n" );
            break;
        }
        printf("%s",read_buf);
    }

    return NULL;
}

void* user_input(void* client_socket) 
{
    char ip_buf[1024];
    int client_sock = *((int*)client_socket);
    while (1) {
        memset(ip_buf, 0, sizeof(ip_buf));
        fgets(ip_buf, sizeof(ip_buf), stdin);
        if (strcmp(ip_buf, "quit") == 0)
        {
            break; // Exit the loop
        }
        int bytesSent = send(client_sock, ip_buf, strlen(ip_buf),0);
        // printf("ip: %d\n",bytesSent);
        if (bytesSent == -1)
        {
            perror("Error sending data to server");
            break;
        }
    }

    return NULL;
}


int main() 
{
    char send_buf[1024], recv_buf[1024];

    // Server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    // Socket connection
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Client socket error.\n");
        exit(1);
    }

    // Client connect
    int client_connect = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (client_connect == -1) {
        perror("Client connect error.\n");
        exit(1);
    }

    pthread_t read_thread,ip_thread;
    
    if(pthread_create(&ip_thread,NULL,user_input,&client_socket)!=0)
    {
        perror("thread creation error.\n");
        exit(1);
    }

    if(pthread_create(&read_thread,NULL,read_input,&client_socket)!=0)
    {
        perror("thread creation error.\n");
        exit(1);
    }

    pthread_join(ip_thread, NULL);
    pthread_join(read_thread, NULL);
    
    close(client_socket);
    return 0;
}