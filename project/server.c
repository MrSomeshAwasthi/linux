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
#include "authen.h"


bool handle_client(int client_socket) 
{   
    int choice=0;
    printf("........................................Welcome Back To Academia :: Course Registration........................................\n");
    printf("Login Type");
    printf("\n Enter Your Choice {1. Admin , 2. Professor, 3. Student} : ");
    int bytes_received = recv(client_socket, &choice, sizeof(choice), 0);
    //send(client_socket, &choice, sizeof(choice), 0);
    if (authen(client_socket,choice)) {
        send(client_socket, "Authentication successful", sizeof("Authentication successful"), 0);
        return true;
    } else {
        send(client_socket, "Authentication failed", sizeof("Authentication failed"), 0);
        return false;
    }

    // bool authentic=authen(client_socket);
    // if (authentic==false)
    // {
    //     perror("\ninvalid user");
    //     return false;
    // }
    // return true;
    // // Validate credentials (replace with your authentication logic)
    // if (strcmp(username, "user123") == 0 && strcmp(password, "pass123") == 0) {
    //     send(client_socket, "Authentication successful", sizeof("Authentication successful"), 0);
    // } else {
    //     send(client_socket, "Authentication failed", sizeof("Authentication failed"), 0);
    // }
}

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

        // Handle the client's login
        handle_client(client_socket);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

// void handle_client(int s_socket_accept) {
//     char recv_buf[1024],send_buf[1024];
//     int read_bytes;

//     while (1) {
//         memset(recv_buf, 0, sizeof(recv_buf));
//         read_bytes = recv(s_socket_accept, recv_buf, sizeof(recv_buf), 0);
//         if (read_bytes <= 0) {
//             perror("Error reading from client");
//             break;
//         }

//         printf("C: %s", recv_buf);

//         printf("S: ");
//         fgets(send_buf, sizeof(send_buf), stdin);

//         if (send(s_socket_accept, send_buf, strlen(send_buf), 0) == -1) {
//             perror("Error writing to client");
//             break;
//         }
//     }
//     close(s_socket_accept);
// }

// 
//     while (1) {
//         // server accept to connect to client
//         struct sockaddr_in client_address;
//         socklen_t addr_len = sizeof(client_address);
//         int s_socket_accept = accept(server_socket, (struct sockaddr *)&client_address, &addr_len);
//         if (s_socket_accept == -1) {
//             perror("server accept error");
//             exit(1);
//         }

//         printf("Got the connection from %s:%d\n", inet_ntoa(client_address.sin_addr), client_address.sin_port);

//         if (fork() == 0) {
//             printf("Created a new process\n");
//             handle_client(s_socket_accept);
//             exit(0);
//         } else {
//             close(s_socket_accept);
//         }
//     }

//     close(server_socket);
//     return 0;
// }