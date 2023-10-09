/*
==================================================================================================
Name : 14.c
Author : Somesh Awasthi
Description :Write a simple program to create a pipe, write to the pipe, read from pipe and 
display on the monitor
Date: 1st oct, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
int main()
{
    int pipefd[2];
    char buff[100], buf[100];
    int pipes=pipe(pipefd);
    if(pipes==-1)
    {
        perror("error in creating pipe");
        return 0;
    }
    printf("enter data: ");
    fgets(buff,sizeof(buff),stdin);
    if(write(pipefd[1],buff,sizeof(buff))==-1)
    {
        perror("error in writing");
        return 0;
    }
    printf("write success\n");
    if(read(pipefd[0],buf,sizeof(buf))==-1)
    {
        perror("error in reading");
        return 0;
    }
    printf("\ndata read: %s",buf);
    printf("\nread success");
    return 0;
}