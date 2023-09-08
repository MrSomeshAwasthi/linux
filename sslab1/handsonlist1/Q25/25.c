/*
====================================================================================
Name : 25.c
Author : Somesh Awasthi
Description :Write a program to create three child processes. 
The parent should wait for a particular child (use waitpid system call).
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include <sys/wait.h>
int main()
{
    int pids[3];
    int status,child1,child2,child3;
    child1=fork();
    if(child1>0)
    {
        printf("child 1 created: %d\n",child1);
        pids[0]=child1;
        child2=fork();
        if (child2>0)
        {
            printf("child 2 created: %d\n",child2);
            pids[1]=child2;
            child3=fork();
            if (child3>0)
            {
                printf("child 3 created: %d\n",child3);
                pids[2]=child3;
                int a=waitpid(pids[2],&status,WUNTRACED);
                //printf("")
            }
            
        }
    }
}