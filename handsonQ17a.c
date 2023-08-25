/*
IT'S A continious project check handsonQ17b also. 
17. Write a program to simulate online ticket reservation. Implement write lock
AIM : Write a program to open a file, store a ticket number and exit. 
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int file_descriptor=open("fileQ17",O_RDWR);
    int ticket_num=1;
    write(file_descriptor,&ticket_num,sizeof(int));
    close(file_descriptor);
    printf("your ticket number: %d\n",ticket_num);
    printf("ticket updated successfully \n");
    return 0;


}