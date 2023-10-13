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
#include"authen.h"

void query(int client_socket,struct sockaddr_in client_address) 
{   
    char read_buf[1024];
    int choice;

    char buf[1024] = "\n..............Welcome Back To Academia :: Course Registration..............\n\nPlease select your login type\n\n1. Admin\n2. Faculty\n3. Student\n4. Exit\nEnter Login Type : \n";
    
    send(client_socket,buf,strlen(buf),0);
    memset(read_buf,0,1024);
    int bytes_received = recv(client_socket, read_buf, sizeof(read_buf), 0);
    choice=atoi(&read_buf[0]);
    if (choice < 1 || choice > 4)
    { 
        send(client_socket,"invalid input\n",sizeof("invalid input\n"),0);
        return;
    }
    else if(choice==4)
    {
        send(client_socket,"BYE\n",sizeof("BYE\n"),0);
        return;
    }


    // authentication
    if (authen(client_socket,client_address,choice)) {
        send(client_socket, "Authentication successful", sizeof("Authentication successful"), 0);
        return;
    } 
    
    else {
        send(client_socket, "Authentication failed", sizeof("Authentication failed"), 0);
        return;
    }


    switch (choice)
    {
    case 1:
        /* show menu*/
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;

    default:
        break;
    }
    return;
}