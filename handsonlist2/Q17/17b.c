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
//implementation through dup2
#include<stdio.h>
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
        dup2(pipefd[1],1);
        execlp("ls","ls","-l",NULL);
    }
    if(!fork())
    {
        //closing std i/p and pipe write fd close
        close(0);
        close(pipefd[1]);
        dup2(pipefd[0],0);
        execlp("wc","wc",NULL);
    }
    return 0;
}