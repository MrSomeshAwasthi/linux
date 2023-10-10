/*
==================================================================================================
Name : 20.c
Author : Somesh Awasthi
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 1st oct, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char buf[100];
    int file_descriptor=open("pipe1",O_RDWR);
    if(read(file_descriptor,buf,sizeof(buf))==-1)
    {
        perror("error in writing");
        return 0;   
    }
    printf("data read : %s",buf);
    return 0;
}