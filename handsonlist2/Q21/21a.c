/*
==================================================================================================
Name : 21.c
Author : Somesh Awasthi
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 1st oct, 2023.
==================================================================================================
*/
// 2 way communication
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char buf[100],buff[100];
    int file_descriptor1=open("pipe1",O_RDWR);
    int file_descriptor2=open("pipe2",O_RDWR);
    printf("21a (active)\n");
    fgets(buf,sizeof(buf),stdin);
    if(write(file_descriptor1,buf,sizeof(buf))==-1)
    {
        perror("error in writing");
        return 0;   
    }
    printf("21a (write) success\n");
    if(read(file_descriptor2,buff,sizeof(buff))==-1)
    {
        perror("error in writing");
        return 0;   
    }
    printf("21a (data read): %s",buff);
    printf("read success\nend 21a\n");
return 0;
}