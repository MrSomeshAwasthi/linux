/*
====================================================================================
Name : 20.c
Author : Somesh Awasthi
Description :Find out the priority of your running program. Modify the priority 
with nice command.
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>
int main()
{
    printf("current priority: %d\n",getpriority(PRIO_PROCESS,0));
    nice(-5);
    printf("modifed priority: %d\n",getpriority(PRIO_PROCESS,0));
    return 0;
}   