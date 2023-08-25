// 6. Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    char buffer[10];
    int file_reader=read(0,buffer,sizeof(buffer));
    printf("character read: %d\n",file_reader);
    write(1,buffer,sizeof(buffer));
    printf("write successful \n");
    return 0;
}