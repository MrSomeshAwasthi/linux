/*
==================================================================================================
Name : 15.c
Author : Somesh Awasthi
Description :  Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2 
                c. use fcntl  
Date: 1st oct, 2023.
==================================================================================================
*/
//implementation through fcntl
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int pipefd[2];
    int pipes=pipe(pipefd);
    if(fork())
    {
        //closing std o/p and pipe read fd close
        close(1);
        close(pipefd[0]);
        fcntl(pipefd[1],F_DUPFD);
        execlp("ls","ls","-l",NULL);
    }
    if(!fork())
    {
        //closing std i/p and pipe write fd close
        close(0);
        close(pipefd[1]);
        fcntl(pipefd[0],F_DUPFD);
        execlp("wc","wc",NULL);
    }
    return 0;
}