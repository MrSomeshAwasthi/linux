/*
==================================================================================================
Name : 24.c
Author : Somesh Awasthi
Description : Write a program to create a message queue and print the key and message queue id. 
Date: 1st oct, 2023.
==================================================================================================
*/
#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
int main()
{
    key_t key=ftok(".",'s');
    printf("0x%x\n%d\n",key,msgget(key,IPC_CREAT | IPC_EXCL | 0766));
    return 0;
}