/*
22. Write a program, open a file, call fork, and then write to the file by both the child as well as the
parent processes. Check output of the file.
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char buff[100];
    int file_descriptor=open("fileQ22",O_RDWR|O_CREAT,0666);
    int pid=fork();
    if(pid==0)
    {
        printf("in child process\n");
        printf("enter thing to write in child process\n");
        read(1,buff,sizeof(buff));
        write(file_descriptor,buff,sizeof(buff));
        printf("\nend child.\n");
    }
    else
    {
        printf("in parent process\n");
        printf("enter thing to write in parent process\n");
        read(1,buff,sizeof(buff));
        write(file_descriptor,buff,sizeof(buff));
        printf("\nend parent.\n");
    }
    return 0;
}