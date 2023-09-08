/*
===============================================================================
Name : 4.c
Author : Somesh Awasthi
Description :Write a program to open an existing file with read write mode.
Try O_EXCL flag also. 
Date: 28th Aug, 2023.
===============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    const char *data="Now Im writing through CLI";
    int file_descriptor=open("file",O_RDWR | O_CREAT | O_EXCL, 0666);
    write(file_descriptor,data,strlen(data));
    if(file_descriptor<0)
    {
        perror("error in opening file");
        return 1;
    }
close(file_descriptor);
return 0; 
}
