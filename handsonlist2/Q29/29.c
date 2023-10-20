/*
==================================================================================================
Name : 29.c
Author : Somesh Awasthi
Description : Write a program to remove the message queue.  
Date: 1st oct, 2023.
==================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int key;
    int msqid;

    key = ftok(".", 29); 
    if (key == -1) {
        perror("Error in ftok");
        return 1;
    }

    msqid = msgget(key, IPC_CREAT|0744);
    if (msqid == -1) {
        perror("Error in msgget");
        return 1;
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("Error in msgctl");
        return 1;
    }

    printf("Message queue removed successfully.\n");

    return 0;
}