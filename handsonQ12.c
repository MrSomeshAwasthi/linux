/*
12. Write a program to find out the opening mode of a file. Use fcntl.
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
int main(void)
{
    int file_descriptor=open("fileQ12",O_RDONLY);
    if(file_descriptor<0)
    {
        perror("error in opening file\n");
        return 0;
    }
    int flag = fcntl(file_descriptor, F_GETFL);
    if ((flag & O_ACCMODE) == O_RDONLY)
        printf("file is in read only mode\n");
    else if ((flag & O_ACCMODE) == O_RDWR)
        printf("file is in read-write only mode\n");
    else if ((flag & O_ACCMODE) == O_WRONLY)
        printf("file is in write only mode\n");    
    else
        printf("no\n");
    return 0;
}
