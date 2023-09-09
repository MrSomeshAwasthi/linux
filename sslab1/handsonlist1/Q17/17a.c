/*
====================================================================================
Name : 17.c
Author : Somesh Awasthi
Description :Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int file_descriptor=open("file",O_RDWR|O_CREAT|O_EXCL,0666);
    char ticket_num='1';
    write(file_descriptor,&ticket_num,sizeof(char));
    printf("your ticket number: %c\n",ticket_num);
    printf("ticket updated successfully \n");
    close(file_descriptor);
    return 0;


}