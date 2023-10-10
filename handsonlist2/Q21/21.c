/*
==================================================================================================
Name : 21.c
Author : Somesh Awasthi
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 1st oct, 2023.
==================================================================================================
*/
//this file will only create fifo 
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
    if(mkfifo("pipe1",0666)==-1)
    {
        perror("fifo error");
        return 0;
    }
    if(mkfifo("pipe2",0666)==-1)
    {
        perror("fifo error");
        return 0;
    }
    return 0;
}