/*
==================================================================================================
Name : 23.c
Author : Somesh Awasthi
Description : Write a program to print the maximum number of files can be opened within a process
              and size of a pipe (circular buffer).
Date: 1st oct, 2023.
==================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
int main()
{
    long pipe1,maxfile;
    pipe1=pathconf("pipe",_PC_PIPE_BUF);
    maxfile=sysconf(_SC_OPEN_MAX);
    printf("%ld\n%ld\n`",pipe1,maxfile);
    return 0;
}