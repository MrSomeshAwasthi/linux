/*
====================================================================================
Name : 18.c
Author : Somesh Awasthi
Description :Write a program to perform Record locking.
 a. Implement write lock
 b. Implement read lock
Create three records in a file. Whenever you access a particular record, 
first lock it then modify/access to avoid race condition.
Date: 28th Aug, 2023.
====================================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define RECORD_SIZE sizeof(struct Record)
struct Record {
    int id;
    char data[100];
};
void wlock(int file_descriptor, off_t offset) {
    struct flock l;
    l.l_type = F_WRLCK;    // Write lock
    l.l_whence = SEEK_SET;
    l.l_start = offset;
    l.l_len = RECORD_SIZE;
    fcntl(file_descriptor, F_SETLKW, &l);
}

void rlock(int file_descriptor, off_t offset) {
    struct flock l;
    l.l_type = F_RDLCK;    // Read lock
    l.l_whence = SEEK_SET;
    l.l_start = offset;
    l.l_len = RECORD_SIZE;
    fcntl(file_descriptor, F_SETLKW, &l);
}
void rellock(int file_descriptor, off_t offset) {
    struct flock lock;
    lock.l_type = F_UNLCK;    // Release lock
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = RECORD_SIZE;
    fcntl(file_descriptor, F_SETLK, &lock);
}
int main()
{
    int file_descriptor=open("fileQ18",O_RDWR|O_CREAT,0666);
    struct Record a[3];
    int choice,rd;
    char buffer[RECORD_SIZE];
    for (int i = 0; i < 3; i++) {
        a[i].id = i + 1;
        sprintf(a[i].data, "Record data %d", i + 1);
        write(file_descriptor, &a[i], RECORD_SIZE);
    }
    printf("enter choice 1. read, 2. write: \n");
    scanf("%d",&choice);
    printf("enter record ID\n");
    scanf("%d",&rd);
    if (rd<1 || rd>3)
    {
        printf("wrong input\n");
        close(file_descriptor);
        return 0;
    }
    off_t offset=(rd-1)*RECORD_SIZE;
    switch (choice)
    {
    case 1:
        printf("stepping into critical section\n");
        rlock(file_descriptor,offset);
        printf("lock acquire\n");
        read(file_descriptor,buffer,RECORD_SIZE);
        printf("read data: %s\n",buffer);  
        break;
    case 2:
        printf("stepping into critical section\n");
        wlock(file_descriptor,offset);
        printf("lock acquire\n");
        printf("enter stuff you want to write \n");
        scanf("%s",buffer);
        write(file_descriptor,buffer,RECORD_SIZE);
        printf("write success\n");
        break;
    default:
        printf("wrong input\n");
        close(file_descriptor);
        return 0;
    }
    //which file you want to update 
    printf("press key to release lock\n");
    getchar();
    getchar();
    rellock(file_descriptor,offset);
    close(file_descriptor);
    return 0;   
}