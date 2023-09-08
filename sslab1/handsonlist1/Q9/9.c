/*
====================================================================================
Name : 9.c
Author : Somesh Awasthi
Description :Write a program to print the following information about a given file.
    a. inode
    b. number of hard links
    c. uid
    d. gid
    e. size
    f. block size
    g. number of blocks
    h. time of last access
    i. time of last modification
    j. time of last change
Date: 28th Aug, 2023.
====================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
    struct stat file_status;
    if (argc!=2)
    {
        printf("error");
        return -1;
    }   
    if (stat(argv[1], &file_status) < 0)
    {
        perror("error");
        return -1;
    }

    printf("a. inode : %lu\n",file_status.st_ino);
    printf("b. number of hard links : %lu\n",file_status.st_nlink);
    printf("c. uid : %d\n",file_status.st_uid);
    printf("d. gid : %d\n",file_status.st_gid);
    printf("e. size : %lu\n",file_status.st_size);
    printf("f. block size : %lu\n",file_status.st_blksize);
    printf("g. number of blocks : %lu\n",file_status.st_blocks);
    printf("h. time of last access : %s\n",ctime(&file_status.st_atime));
    printf("i. time of last modification : %s\n",ctime(&file_status.st_mtime));
    printf("j. time of last change : %s\n",ctime(&file_status.st_ctime));
    return 0;
}