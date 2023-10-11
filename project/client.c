/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/ip.h>
int main()
{
    char send_buf[1024],recv_buf[1024];

    //specifying server ip and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.7");
    
    // socket connection
    int client_socket=socket(AF_INET,SOCK_STREAM,0);
    if(client_socket==-1)
    {
        perror("client socket error.\n");
        exit(1);
    }
    
    // client connect
    int client_connect=connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address));
    if(client_connect==-1)
    {
        perror("client connect error.\n");
        exit(1);
    }
    while (1)
    {    
        //  communicating with server
        printf("C: ");
        fgets(send_buf,sizeof(send_buf),stdin);
        int byte_sent = send(client_socket, send_buf, strlen(send_buf), 0);
        if (byte_sent < 0)
        {
            perror("error sending data");
            exit(1);
        }
        
        memset(recv_buf,0,sizeof(recv_buf));
        int byte_received = recv(client_socket, recv_buf, sizeof(recv_buf), 0);
        if (byte_received < 0)
        {
            perror("error receiving data");
            exit(1);
        }

        printf("S: %s",recv_buf);
    }
    close(client_socket);
    return 0;
}