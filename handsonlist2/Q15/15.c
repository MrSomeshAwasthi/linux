/*
==================================================================================================
Name : 15.c
Author : Somesh Awasthi
Description : Write a simple program to send some data from parent to the child process.
Date: 1st oct, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
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
    if (fork())
    {
        printf("enter data in parent file: ");
        fgets(buff,sizeof(buff),stdin);
        close(pipefd[0]);
        if(write(pipefd[1],buff,sizeof(buff))==-1)
        {
            perror("error in writing");
            return 0;
        }
        printf("write success\n");
    }
    else if (!fork())
    {
        close(pipefd[1]);
        if(read(pipefd[0],buf,sizeof(buf))==-1)
        {
            perror("error in reading");
            return 0;
        }
        printf("\ndata read from child is: %s\n",buf);
        printf("read success\n");
    }
    return 0;
}