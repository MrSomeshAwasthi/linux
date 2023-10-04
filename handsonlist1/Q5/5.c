/*
============================================================================
Name : 5.c
Author : Somesh Awasthi
Description : Write a program to create five new files with infinite loop.
Execute the program in the background and check the file descriptor 
table at /proc/pid/fd.
Date: 28th Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
    // Create five new files
    int fd1 = open("file1",O_RDWR|O_CREAT, 0666);
    printf("File descriptor 1: %d\n",fd1);
    int fd2 = open("file2",O_RDWR|O_CREAT, 0666);
    printf("File descriptor 2: %d\n",fd2);
    int fd3 = open("file3",O_RDWR|O_CREAT, 0666);
    printf("File descriptor 3: %d\n",fd3);
    int fd4 = open("file4",O_RDWR|O_CREAT, 0666);
    printf("File descriptor 4: %d\n",fd4);
    int fd5 = open("file5",O_RDWR|O_CREAT, 0666);
    printf("File descriptor 5: %d\n",fd5);
    for(;;);
    return 0;
}