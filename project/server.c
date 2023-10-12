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

void handle_client(int client_socket) {
    char data_from_client[BUF_SIZE];
    int read_bytes;

    while (1) {
        memset(data_from_client, 0, sizeof(data_from_client));
        read_bytes = recv(client_socket, data_from_client, sizeof(data_from_client), 0);
        if (read_bytes <= 0) {
            perror("Error reading from client");
            break;
        }

        printf("C: %s", data_from_client);

        printf("S: ");
        fgets(data_from_client, sizeof(data_from_client), stdin);

        if (send(client_socket, data_from_client, strlen(data_from_client), 0) == -1) {
            perror("Error writing to client");
            break;
        }
    }
    close(client_socket);
}

int main() {
    char send_buf[BUF_SIZE];
    // socket address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // Port 8080
    server_address.sin_addr.s_addr = INADDR_ANY;

    // socket connection
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("server socket error");
        exit(1);
    }

    // binding server
    int s_socket_bind = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (s_socket_bind == -1) {
        perror("server binding error");
        exit(1);
    }

    // server listen
    int s_socket_listen = listen(server_socket, 5); // Maximum of 5 clients
    if (s_socket_listen == -1) {
        perror("server listening error");
        exit(1);
    }
    printf("server is listening\n");

    while (1) {
        // server accept to connect to client
        struct sockaddr_in client_address;
        socklen_t addr_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addr_len);
        if (client_socket == -1) {
            perror("server accept error");
            exit(1);
        }

        printf("Got the connection from %s:%d\n", inet_ntoa(client_address.sin_addr), client_address.sin_port);

        if (fork() == 0) {
            printf("Created a new process\n");
            handle_client(client_socket);
            exit(0);
        } else {
            close(client_socket);
        }
    }

    close(server_socket);
    return 0;
}


































// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>  
// #include<unistd.h>
// #include<sys/socket.h>
// #include<netinet/in.h>
// void handle_client(int s_socket_accept)
// {
//     char send_buf[1024],recv_buf[1024];
//     while (1)   
//     {
//         // communicate with client
//         memset(recv_buf,0,sizeof(recv_buf));
//         int byte_received = recv(s_socket_accept, recv_buf, sizeof(recv_buf), 0);
//         if(byte_received<0)
//         {
//             perror("insufficient data sent\n");
//             exit(1);
//         }
//         printf("C: %s",recv_buf);
//         printf("S: ");
//         fgets(send_buf,sizeof(send_buf),stdin);
//         send(s_socket_accept, send_buf, strlen(send_buf), 0);   
//     }
        
// }
// int main()
// {
//     // socket address structure
//     // declaring sockaddr_in to for defining address and port to bind
//     struct sockaddr_in server_address;
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(8080);
//     server_address.sin_addr.s_addr = INADDR_ANY;

//     // socket connection
//     int server_socket=socket(AF_INET,SOCK_STREAM,0);
//     if(server_socket==-1)
//     {
//         perror("server socket error.\n");
//         exit(1);
//     }

//     // binding server
//     int s_socket_bind=bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));
//     if(s_socket_bind==-1)
//     {
//         perror("server binding error\n");
//         exit(1);
//     }

//     // server listen 
//     int s_socket_listen=listen(server_socket,10);
//     if(s_socket_listen==-1)
//     {
//         perror("server listening error\n");
//         exit(1);
//     }
//     printf("server is listening\n");



//     while (1)
//     {
//         // server accept to connect to client
//         socklen_t addr_len = sizeof(server_address);
//         int s_socket_accept=accept(server_socket,(struct sockaddr *)&server_address, &addr_len);
//         if(s_socket_accept==-1)
//         {
//             perror("server accept error\n");
//             exit(1);
//         }
//         pid_t child = fork();
//         if(child<0)
//         {
//             perror("fork error");
//             exit(1);
//         }
//         else if (child==0)
//         {
//             close(server_socket);
//             handle_client(s_socket_accept);
//             close(s_socket_accept);
//             exit(0);
//         }
//         else
//         {
//             close(s_socket_accept);
//         }
//     }
//     close(server_socket);
//     return 0;
// }   