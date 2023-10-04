/*
====================================================================================
Name : 22.c
Author : Somesh Awasthi
Description :Write a program, open a file, call fork, and then write to the file
by both the child as well as the parent processes. Check output of the file.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char* argv[])
{
    int file_descriptor=open("file",O_RDWR|O_CREAT,0666);
    int pid=fork();
    if(pid==0)
    {
        printf("in child process\n");
        write(file_descriptor,"hello from child process\n",26);
        printf("write success\nend child.\n");
    }
    else
    {
        sleep(2);
        printf("in parent process\n");
        write(file_descriptor,"hello from parent process\n",27);
        printf("write success\nend parent.\n");
    }
    return 0;
}