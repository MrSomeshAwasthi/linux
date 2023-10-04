/*
==================================================================================================
Name : 14.c
Author : Somesh Awasthi
Description :Write a simple program to create a pipe, write to the pipe, read from pipe and 
display on the monitor
Date: 28th Aug, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>  
int main()
{
    int pipefd[2];
    char buff[100];
    int pipes=pipe(pipefd);
    if(pipes==-1)
    {
        perror("error in creating pipe");
        return 0;
    }
    printf("enter data: ");
    fgets(buff,sizeof(buff),stdin);
    close(pipefd[0]);
    printf("write");
    if(write(pipefd[1],buff,sizeof(buff))==-1)
    {
        perror("error in writing");
        return 0;
    }
    printf("write success");
    close(pipefd[1]);
    printf("read");
    if(read(pipefd[0],buff,sizeof(buff))==-1)
    {
        perror("error in reading");
        return 0;
    }
    close(pipefd[0]);
    printf("read success: %s",buff);
    return 0;
}