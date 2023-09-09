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
        int source = open(argv[1], O_RDONLY);
        int target = open(argv[2], O_WRONLY|O_CREAT);

        if(source==-1 || target==-1)
                printf("error in reading or writing in a file.\n");

        // Logic
        while(1){
                char buf;
                int read_byte = read(source, &buf, 1);

                if(read_byte==0)
                        break;

                int write_bytes = write(target, &buf, 1);
        }
        int close_fd_read = close(source);
        int close_fd_write = close(target);

        if(close_fd_read==-1 || close_fd_write==-1)
                printf("error in closing file\n");

        return 0;

}