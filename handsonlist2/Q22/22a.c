/*
==================================================================================================
Name : 22.c
Author : Somesh Awasthi
Description : Write a program to wait for data to be written into FIFO within 10 seconds,
              use select system call with FIFO.
Date: 1st oct, 2023.
==================================================================================================
*/
//creating fifo
#include <stdio.h>    
#include <fcntl.h>     
#include <unistd.h>    
#include <sys/time.h>  
#include <sys/stat.h>  
#include <sys/types.h> 
void main()
{
    int file_descriptor, rd_fd;
    char buf[100];
    fd_set readme;
    struct timeval timer;
    int result;
    file_descriptor = open("pipe1", O_NONBLOCK | O_RDONLY);
    if (file_descriptor == -1)
    {
        perror("ERROR");
        _exit(0);
    }
    FD_ZERO(&readme);
    FD_SET(file_descriptor, &readme); 
    timer.tv_sec = 10;
    timer.tv_usec = 0;
    result = select(file_descriptor + 1, &readme, NULL, NULL, &timer);
    if (result == -1)
        perror("Error");
    else if (result)
    {
        rd_fd = read(file_descriptor, &buf, 100);

        if (rd_fd == -1)
            perror("Error");
        else
            printf("data read : %s\n", buf);
    }
    else
        printf("TIMEOUT! NO data\n");
    close(file_descriptor);
}