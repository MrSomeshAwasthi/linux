/*
====================================================================================
Name : 12.c
Author : Somesh Awasthi
Description :Write a program to find out the opening mode of a file. Use fcntl.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
int main()
{
    int file_descriptor=open("file",O_RDWR);
    if(file_descriptor<0)
    {
        perror("error in opening file\n");
        return 0;
    }
    int flag = fcntl(file_descriptor, F_GETFL);
    printf("%d\n",flag);
    if ((flag & O_ACCMODE) == O_RDONLY)
        printf("file is in read only mode\n");
    else if ((flag & O_ACCMODE) == O_RDWR)
        printf("file is in read-write only mode\n");
    else if ((flag & O_ACCMODE) == O_WRONLY)
        printf("file is in write only mode\n");    
    else
        printf("no\n");
    return 0;
}