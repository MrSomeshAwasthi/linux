/*
====================================================================================
Name : 21.c
Author : Somesh Awasthi
Description :Write a program, call fork and print the parent and child process id.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    printf("you are in the parent program\nforking...\n");
    if (!fork())
        printf("child pid: %d\n",getpid());
    else
        printf("parent pid: %d\n",getpid());
    return 0;
}
