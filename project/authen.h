/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>

char username[128],password[128],temp[128];

bool admin(int client_socket)
{
    printf("\nEnter the username: ");
    // Read username from client
    int username_bytes = recv(client_socket, username, sizeof(username), 0);
    if (username_bytes <= 0) 
    {
        perror("Error reading username from client");
        return false;
    }
    username[username_bytes] = '\0';


    //FILE *admin_file = fopen("data/user_data.txt", "r");

    
    if (strcmp(username, "admin") != 0)
    {
        memset(username, 0, sizeof(username));
        perror("Invalid username");
        return false;
    }   


    printf("\nEnter the password: ");
    // Read password from client
    int password_bytes = recv(client_socket, password, sizeof(password), 0);
    if (password_bytes <= 0) 
    {
        perror("Error reading password from client");
        return false;
    }
    password[password_bytes] = '\0';


    if (strcmp(password, "admin") != 0)
    {
        memset(password, 0, sizeof(password));
        perror("Invalid password");
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


bool authen(int client_socket,int choice)
{

    bool ans;
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    
    int bytes_received = recv(client_socket, temp, sizeof(temp), 0);
    if (bytes_received <= 0) {
        perror("Error reading choice from client");
        return false;
    }

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
    
    default:
        break;
    }
    return ans;
}