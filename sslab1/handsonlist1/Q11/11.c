/*
==========================================================================================
Name : 11.c
Author : Somesh Awasthi
Description :Write a program to open a file, duplicate the file descriptor and append
the file with both the descriptors and check whether the file is updated properly or not.
 a. use dup
 b. use dup2
 c. use fcntl
Date: 28th Aug, 2023.
===========================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int file_descriptor,dup_fd, dup2_fd,dup3_fd;
    file_descriptor = open ("file" , O_RDWR | O_CREAT , 0666);
    if(file_descriptor<0)
    {
        perror("error in opening file\n");
        return 0;
    }
    //duplicate the file_descriptor in dup_fd
        write(file_descriptor,"duplicate using dup1\n",sizeof("duplicate using dup1\n"));
        dup_fd=dup(file_descriptor);
        if (dup_fd<0)
        {
            perror("1. error in duplicating fd\n");
            return 0;
        }
        char buf[]="-> this is a test text \n";
        write(file_descriptor,&buf,sizeof(buf));
        write(dup_fd,&buf,sizeof(buf));
    // duplicate the file_descriptor in dup2_fd
        write(file_descriptor,"duplicate using dup2\n",sizeof("duplicate using dup2\n"));
        dup2(file_descriptor,dup2_fd);
        if (dup2_fd<0)
        {
            perror("2. error in duplicating fd\n");
            return 0;
        }
        write(file_descriptor,&buf,sizeof(buf));
        write(dup_fd,&buf,sizeof(buf));
    // duplicate the file_descriptor in dup3_fd (fcntl)
        write(file_descriptor,"duplicate using fcntl\n",sizeof("duplicate using fcntl\n"));
        dup3_fd=fcntl(file_descriptor,F_DUPFD);
        if (dup3_fd<0)
        {
            perror("3. error in duplicating fd\n");
            return 0;
        }
        write(file_descriptor,&buf,sizeof(buf));
        write(dup_fd,&buf,sizeof(buf));
      
    return 0;
}