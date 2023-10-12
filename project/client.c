/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

int main() {
    char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];

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

    while (1) {
        // Communicating with the server
        printf("C: ");
        fgets(send_buf, sizeof(send_buf), stdin);
        int byte_sent = send(client_socket, send_buf, strlen(send_buf), 0);
        if (byte_sent < 0) {
            perror("Error sending data");
            exit(1);
        }

        memset(recv_buf, 0, sizeof(recv_buf));
        int byte_received = recv(client_socket, recv_buf, sizeof(recv_buf), 0);
        if (byte_received < 0) {
            perror("Error receiving data");
            exit(1);
        }

        printf("S: %s", recv_buf);
    }
    close(client_socket);
    return 0;
}