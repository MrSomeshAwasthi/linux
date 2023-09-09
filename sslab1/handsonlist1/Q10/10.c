/*
====================================================================================
Name : 10.c
Author : Somesh Awasthi
Description :Write a program to open a file with read write mode, write 10 bytes, 
move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
    a. check the return value of lseek
    b. open the file with od and check the empty spaces in between the data.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>   
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
    int file_descriptor = open("file",O_RDWR|O_CREAT,0666);
    if (file_descriptor<0)
    {
        perror("error in opening a file");
        return 0;
    }
    int bytes_write = write(file_descriptor,"space of 10 bytes ",sizeof("space of 10 bytes "));
    if (bytes_write<0)
    {
        perror("write error");
        return 0;
    }
    off_t return_lseek = lseek(file_descriptor,10,SEEK_CUR);
    bytes_write=write(file_descriptor,"second time typing 10 bytes",sizeof("second time typing 10 bytes"));
    if (bytes_write<0)
    {
        perror("write error");
        return 0;
    }
    printf("the return value of lseek is %ld\n",return_lseek);
    return 0;
}