/*
==================================================================================================
Name : 21.c
Author : Somesh Awasthi
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 1st oct, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char buf[100],buff[100];
    int file_descriptor1=open("pipe1",O_RDWR);
    int file_descriptor2=open("pipe2",O_RDWR);
    printf("21b (active)\n");
    if(read(file_descriptor1,buff,sizeof(buff))==-1)
    {
        perror("error in writing");
        return 0;   
    }
    printf("data read: %s",buff);
    printf("read success\n");
    fgets(buf,sizeof(buf),stdin);
    if(write(file_descriptor2,buf,sizeof(buf))==-1)
    {
        perror("error in writing");
        return 0;   
    }
    printf("write success\nend 21b\n");
return 0;
}