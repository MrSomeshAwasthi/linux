/*
24. Write a program to create an orphan process.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
int main()
{
    int pid=fork();   
    if (pid>0)
    {
        printf("parent pid is: %d\n",getpid());
        exit(0);
    }
    else
    {
        printf("child pid is: %d\n",getpid());
        sleep(70);
        exit(0);
    }
}