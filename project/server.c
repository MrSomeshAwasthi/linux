/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>  
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
    char send_buf[1024],recv_buf[1024];
    // socket address structure
    // declaring sockaddr_in to for defining address and port to bind
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // socket connection
    int server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket==-1)
    {
        perror("server socket error.\n");
        exit(1);
    }

    // binding server
    int s_socket_bind=bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));
    if(s_socket_bind==-1)
    {
        perror("server binding error\n");
        exit(1);
    }

    // server listen 
    int s_socket_listen=listen(server_socket,10);
    if(s_socket_listen==-1)
    {
        perror("server listening error\n");
        exit(1);
    }
    printf("server is listening\n");

    // server accept to connect to client
    socklen_t addr_len = sizeof(server_address);
    int s_socket_accept=accept(server_socket,(struct sockaddr *)&server_address, &addr_len);
    if(s_socket_accept==-1)
    {
        perror("server accept error\n");
        exit(1);
    }


    while (1)
    {
        // communicate with client
        memset(recv_buf,0,sizeof(recv_buf));
        int byte_received = recv(s_socket_accept, recv_buf, sizeof(recv_buf), 0);
        if(byte_received<0)
        {
            perror("insufficient data sent\n");
            exit(1);
        }
        printf("C: %s",recv_buf);
        printf("S: ");
        fgets(send_buf,sizeof(send_buf),stdin);
        send(s_socket_accept, send_buf, strlen(send_buf), 0);   
    }
    close(s_socket_accept);
    close(server_socket);
    return 0;
}   