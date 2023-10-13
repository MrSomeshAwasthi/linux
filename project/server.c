/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "query.h"

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;


    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Server socket error");
        exit(1);
    }


    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Binding error");
        exit(1);
    }

    // Listen for clients
    if (listen(server_socket, 5) < 0) {
        perror("Listening error");
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
        socklen_t client_address_len = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("server accept error");
            continue;
        }
        //inet_ntoa-(convert into human readable IP)
        //ntohs-(convert into human readable port)
        printf("Connection established with %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        if (!fork())
        {
            printf("new process created\n");
            // Handle the client's query
            query(client_socket,client_address);
        }
        close(client_socket);
    }

    close(server_socket);
    return 0;
}