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

#include "admin_fun.h"
char username[128],password[128],tmp[1024];

bool admin(int client_socket)
{
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "\nEnter the username: \n");
    send(client_socket, tmp, strlen(tmp), 0);
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


bool facultys(int client_socket)
{
    char username[10],password[10];
    int fd = open("data/faculty.txt", O_RDONLY);


    if (fd == -1)
    {
        perror("Error opening file");
        return false;
    }


    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "\nEnter the username: \n");
    send(client_socket, tmp, strlen(tmp), 0);
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

    struct faculty f;
     lseek(fd,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd, &f, sizeof(struct faculty)) > 0)
    {
        if (strcmp((username, f.username) || (password, f.password) ) != 0)
        {
            memset(tmp, 0, sizeof(tmp));
            strcpy(tmp, "Invalid username and password\n");
            memset(username, 0, sizeof(username));
            send(client_socket, tmp, strlen(tmp), 0);
            return false;
        } 
        return true;
    }

}


bool students(int client_socket)
{

    char username[10],password[10];
    int fd = open("data/student.txt", O_RDONLY);


    if (fd == -1)
    {
        perror("Error opening file");
        return false;
    }


    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "\nEnter the username: \n");
    send(client_socket, tmp, strlen(tmp), 0);
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

    struct student s;
     lseek(fd,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd, &s, sizeof(struct student)) > 0)
    {
        if (strcmp((s.username, username) || (s.password, password) ) != 0)
        {
            memset(tmp, 0, sizeof(tmp));
            strcpy(tmp, "Invalid username and password\n");
            memset(username, 0, sizeof(username));
            send(client_socket, tmp, strlen(tmp), 0);
            return false;
        } 
        return true;
    }

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
            ans=facultys(client_socket);
            break;
        case 3:
            ans=students(client_socket);
            break;
    }
    return ans;
}