/*
14. Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(int argc , char *argv[])
{
    int pipefd[2];
    char buff;
    if (argc!=2)
    {
        return 0;
    }
    if (pipe(pipefd)<0)
        {
            perror("pipe not created");
            return 0;
        }
    close(pipefd[1]);
    while (read(pipefd[0],&buff,1)>0)
    {
        write(STDOUT_FILENO,&buff,1);
    }
    close(pipefd[0]);
    write(1,argv[1],strlen(argv[1]));
    close(pipefd[1]);    
    printf("\n");
    return 0;
}