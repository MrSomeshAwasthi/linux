/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

char username[10],password[10],tmp[1024];

bool admin(int client_socket)
{
    char username[6],password[6],tmp[1024];
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

    struct student f;
     lseek(fd,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd, &f, sizeof(struct student)) > 0)
    {
        if (strcmp(username, f.username) == 0 && strcmp(password, f.password) == 0)
        {
            return true;
        } 
    }
    return false;
}

bool students(int client_socket)
{

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
        if (strcmp(username, s.username) == 0 && strcmp(password, s.password) == 0 )
        {
            if (s.status)
                return true;
        } 
    }
    return false;

}

bool authen(int client_socket,struct sockaddr_in client_address,int choice)
{

    bool ans=false;
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    
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