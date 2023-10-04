/*
===============================================================================
Name : 6.c
Author : Somesh Awasthi
Description : Write a program to take input from STDIN and display on STDOUT.
Use only read/write system calls
Date: 28th Aug, 2023.
===============================================================================
*/
#include<stdio.h>
#include<unistd.h>
int main()
{
    char buffer[10];
    if(read(0,buffer,sizeof(buffer))<0)
    {
        perror("read error");
        return 0;
    }
    if(write(1,buffer,sizeof(buffer))<0)
    {
        perror("write error");
        return 0;
    }
    return 0;
}