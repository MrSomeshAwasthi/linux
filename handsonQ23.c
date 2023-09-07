/*
23. Write a program to create a Zombie state of the running program.
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
        sleep(60);
        exit(0);
    }
    else
    {
        printf("hi kid your pid is: %d\n",getpid());
        exit(0);
    }
    
    return 0;
}
/*
    after running program do in another terminal 
     cd /proc
     cd pid
     cat status
*/