/*
====================================================================================
Name : 27.c
Author : Somesh Awasthi
Description :27. Write a program to execute ls -Rl by the following system calls
    a. execl
    b. execlp
    c. execle
    d. execv
    e. execvp
Date: 28th Aug, 2023.
====================================================================================
*/
#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("b. using execlp: \n");
    execlp("ls","ls", "-Rl",(char *) NULL);
	return 0;
}