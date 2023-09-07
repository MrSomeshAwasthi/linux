/*
22. Write a program, open a file, call fork, and then write to the file by both the child as well as the
parent processes. Check output of the file.
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char* argv[])
{
    //char buff[20];
    int file_descriptor=open("fileQ22",O_RDWR|O_CREAT,0666);
    int pid=fork();
    if(pid==0)
    {
        printf("in child process\n");
        write(file_descriptor,"hello from child process\n",26);
        printf("\nend child.\n");
    }
    else
    {
        sleep(2);
        printf("in parent process\n");
        write(file_descriptor,"hello from parent process\n",27);
        printf("\nend parent.\n");
    }
    return 0;
}