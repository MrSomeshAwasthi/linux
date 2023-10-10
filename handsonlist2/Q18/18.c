/*
==================================================================================================
Name : 18.c
Author : Somesh Awasthi
Description :  Write a program to find out total number of directories on the pwd.
                execute ls -l | grep ^d | wc ? Use only dup2. 
Date: 1st oct, 2023.
==================================================================================================
*/
//implementation through dup2
#include<stdio.h>
#include<unistd.h>
int main()
{
    int pipefd1[2],pipefd2[2];
    int pipe1=pipe(pipefd1);
    int pipe2=pipe(pipefd2);
    if(fork())
    {
        //closing std o/p and pipe read fd close
        close(1);
        close(pipefd1[0]);
        dup2(pipefd1[1],1);
        execlp("ls","ls","-l",NULL);
    }

    if(!fork())
    {
        if(fork())
        {
            //closing std i/p and o/p and pipe write fd close
            close(0);
            close(1);
            close(pipefd1[1]);
            close(pipefd2[0]);
            dup2(pipefd1[0],0);
            dup2(pipefd2[1],1);
            execlp("grep","grep","^d",NULL);
        }
        else
        {
            //closing std i/p and pipe write fd close
            close(0);
            close(pipefd1[0]);
            close(pipefd2[1]);
            close(pipefd1[1]);
            dup2(pipefd2[0],0);
            execlp("wc","wc",NULL);
        }
    }
    return 0;
}