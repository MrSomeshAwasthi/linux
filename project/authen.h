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

char username[128],password[128],tmp[1024];

bool admin(int client_socket)
{
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "\nEnter the username: \n");
    send(client_socket, tmp, strlen(tmp), 0);
    // printf("\nEnter the username: ");
    // Read username from client
    int username_bytes = recv(client_socket, username, sizeof(username), 0);
    if (username_bytes <= 0) 
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "Error reading username from client\n");
        send(client_socket,tmp,sizeof(tmp),0);
        return false;
    }
    username[username_bytes-1] = '\0';

    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "\nEnter the password: \n");
    send(client_socket,tmp,sizeof(tmp),0);
    // Read password from client
    int password_bytes = recv(client_socket, password, sizeof(password), 0);
    if (password_bytes <= 0) 
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "Error reading password from client\n");
        send(client_socket,tmp,sizeof(tmp),0);
        return false;
    }
    password[password_bytes-1] = '\0';

    if ((strcmp(username, "admin") || strcmp(password, "admin")) != 0)
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "Invalid username and password\n");
        memset(username, 0, sizeof(username));
        send(client_socket, tmp, strlen(tmp), 0);
        return false;
    } 

    return true;
}


bool faculty(int client_socket)
{

}


bool student(int client_socket)
{

}


bool authen(int client_socket,struct sockaddr_in client_address,int choice)
{

    bool ans=false;
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    
    // int bytes_received = recv(client_socket, temp, sizeof(temp), 0);
    // if (bytes_received <= 0) {
    //     perror("Error reading choice from client");
    //     return false;
    // }
    
    switch (choice)
    {
        case 1:
            ans=admin(client_socket);
            break;
        case 2:
            ans=faculty(client_socket);
            break;
        case 3:
            ans=student(client_socket);
            break;
    }
    return ans;
}