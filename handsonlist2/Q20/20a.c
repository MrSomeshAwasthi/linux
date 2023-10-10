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
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
    char buf[100];
    if(mkfifo("pipe1",0666)==-1)
    {
        perror("fifo error");
        return 0;
    }
    int file_descriptor=open("pipe1",O_RDWR);
    fgets(buf,sizeof(buf),stdin);
    if(write(file_descriptor,buf,sizeof(buf))==-1)
    {
        perror("error in writing");
        return 0;   
    }
    return 0;
}