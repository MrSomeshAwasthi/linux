/*
============================================================================
Name : 7.c
Author : Somesh Awasthi
Description :Write a program to copy file1 into file2 ($cp file1 file2).
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
        if(argc!=3)
        {
                printf("enter proper arguments\n");
                return -1;
        }
        int fd_read = open(argv[1], O_RDONLY);
        int fd_write = open(argv[2], O_WRONLY|O_CREAT);

        if(fd_read==-1 || fd_write==-1)
                printf("error in reading or writing in a file.\n");

        // Logic
        while(1){
                char buf;
                int read_byte = read(fd_read, &buf, 1);

                if(read_byte==0)
                        break;

                int write_bytes = write(fd_write, &buf, 1);
        }
        int close_fd_read = close(fd_read);
        int close_fd_write = close(fd_write);

        if(close_fd_read==-1 || close_fd_write==-1)
                printf("error in closing file\n");

        return 0;

}