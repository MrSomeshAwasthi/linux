/*
21. Write a program, call fork and print the parent and child process id.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    printf("you are in the parent program\nforking...\n");
    if (!fork())
        printf("child pid: %d\n",getpid());
    else
        printf("parent pid: %d\n",getppid());
    return 0;
}
