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
#include<sys/wait.h>
#include<unistd.h> 
int main()
{
    int arr[3];
    int status,a,b,c;
    a=fork();
    if(a>0)
    {
        printf("child 1 created: %d\n",a);
        arr[0]=a;
        b=fork();
        if (b>0)
        {
            printf("child 2 created: %d\n",b);
            arr[1]=b;
            c=fork();
            if (c>0)
            {
                printf("child 3 created: %d\n",c);
                arr[2]=c;
                int a=waitpid(arr[2],&status,WUNTRACED);
                printf("terminating Child process with process %d\n",a);
            }            
        }
    }
}