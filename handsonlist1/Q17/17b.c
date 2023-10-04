/*
====================================================================================
Name : 17.c
Author : Somesh Awasthi
Description :Write a program to simulate online ticket reservation. Implement write 
lock Write a program to open a file, store a ticket number and exit. Write a 
separate program, to open the file, implement write lock, read the ticket number,
increment the number and print the new ticket number then close the file.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int file_descriptor=open("file",O_RDWR),num;
    char ticket_num;
    struct flock l;
    l.l_type=F_WRLCK;
    l.l_whence=SEEK_SET;
    l.l_start=0;
    l.l_len=0;
    l.l_pid=getpid();
    fcntl(file_descriptor,F_SETLKW,&l);
    printf("lock attained\n");
    read(file_descriptor,&ticket_num,sizeof(char));
    num = (int)ticket_num+1;
    ticket_num=(char)num;
    lseek(file_descriptor,0,SEEK_SET);
    write(file_descriptor,&ticket_num,sizeof(char));
    printf("ticket number: %c\nstatus updated successfully.\n",ticket_num);
    getchar();
    l.l_type = F_UNLCK;  
    fcntl(file_descriptor, F_SETLK, &l);
    close(file_descriptor);
    return 0;

}