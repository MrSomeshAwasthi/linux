/*
==================================================================================================
Name : 16.c
Author : Somesh Awasthi
Description :  Write a program to send and receive data from parent to child vice versa. Use two 
way communication. 
Date: 1st oct, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int pipefd1[2],pipefd2[2];
    char buf[100],buff[100];
    int pipes_one=pipe(pipefd1);
    int pipes_two=pipe(pipefd2);
    if (pipes_one==-1 || pipes_two==-1)
    {
        perror("error in creating file\n");
        return 0;
    }
    if (!fork())
    {
        close(pipefd1[1]);
        if(read(pipefd1[0],buf,sizeof(buf))==-1)
        {
            perror("error in reading\n");
            return 0;
        }
        printf("read (child): \n");
        printf("data read: %s",buf);
        printf("read success\n");
        close(pipefd2[0]);
        printf("write (child): \n");
        fgets(buff,sizeof(buff),stdin);
        if(write(pipefd2[1],buff,sizeof(buff))==-1)
        {
            perror("error in writing\n");
            return 0;
        }
        printf("write success\n");

    }
    else if (fork())
    {
        close(pipefd1[0]);
        printf("write (parent): \n");
        fgets(buff,sizeof(buff),stdin);
        if(write(pipefd1[1],buff,sizeof(buff))==-1)
        {
            perror("error in writing\n");
            return 0;
        }
        printf("write success\n");
        close(pipefd2[1]);
        if(read(pipefd2[0],buff,sizeof(buff))==-1)
        {
            perror("error in reading\n");
            return 0;
        }
        printf("read (parent): \n");
        printf("data read: %s",buff);
        printf("read success\n");
    }
    return 0;
}