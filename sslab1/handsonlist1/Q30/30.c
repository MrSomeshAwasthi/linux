/*
========================================================================================
Name : 30.c
Author : Somesh Awasthi
Description :Write a program to run a script at a specific time using a Daemon process.
Date: 28th Aug, 2023.
========================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include <time.h>
#define hour 17
#define min 11

#define PATH "/home/somesh/sslab/sslab1/handsonlist1/Q30/extra"

void script()
{
    if(fork())
	{
    	execl(PATH,PATH,(char*)NULL);
    	perror("error");
    }
}
int main()
{
	if(fork()>0)
        exit(0);
	if(setsid()<0) 
	{
        perror("setsid failed");
        exit(1);
    }
    while(1)
	{
        time_t now;
        struct tm *current;
        time(&now);
        current = localtime(&now);
        if(current->tm_hour==hour && current->tm_min== min){
            script();
            sleep(24*3600);
        }
        sleep(1);
    }
}