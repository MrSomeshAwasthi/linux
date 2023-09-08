/*
====================================================================================
Name : 16.c
Author : Somesh Awasthi
Description :Write a program to perform mandatory locking.
 a. Implement write lock
 b. Implement read lock.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int file_descriptor = open("file",O_RDWR|O_CREAT,0666);
    int lt;
    struct flock l;
    printf("select lock type 1. write 2. read \n");
    scanf("%d%*c",&lt);
    fflush(stdin);
    if (lt == 1)
    {
        l.l_type=F_WRLCK;
        l.l_whence=SEEK_SET;
        l.l_start=0;
        l.l_len=0;
        l.l_pid= getpid();
        fcntl(file_descriptor,F_SETLKW,&l);
    }
    else
    {
        l.l_type=F_RDLCK;
        l.l_whence=SEEK_SET;
        l.l_start=0;
        l.l_len=0;
        l.l_pid=getpid();
        fcntl(file_descriptor,F_SETLK,&l);
    }
    //critical section
    printf("you are in critical section\n");
    getchar();
    printf("unlocked\n");
    l.l_type=F_UNLCK;
    fcntl(file_descriptor,F_SETLK,&l);
    return 0;
}