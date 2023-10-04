/*
====================================================================================
Name : 24.c
Author : Somesh Awasthi
Description :Write a program to create an orphan process.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
int main()
{
    int pid=fork();   
    if (pid>0)
    {
        printf("parent pid is: %d\n",getpid());
        exit(0);
    }
    else
    {
        printf("child pid is: %d\n",getpid());
        sleep(70);
        exit(0);
    }
}