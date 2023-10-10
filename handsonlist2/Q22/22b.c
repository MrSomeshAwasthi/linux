/*
==================================================================================================
Name : 22.c
Author : Somesh Awasthi
Description : Write a program to wait for data to be written into FIFO within 10 seconds,
              use select system call with FIFO.
Date: 1st oct, 2023.
==================================================================================================
*/
#include <stdio.h>    
#include <fcntl.h>     
#include <unistd.h>   
#include <sys/stat.h>  
#include <sys/time.h> 
#include <sys/types.h>

int main()
{
    int filedescriptor, wr_fd;
    char buf[100];

    filedescriptor = open("pipe1", O_NONBLOCK | O_WRONLY);
    fgets(buf,sizeof(buf),stdin);
    wr_fd = write(filedescriptor, buf, sizeof(buf));
    return 0;
}