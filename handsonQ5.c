// //5. Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
    int file_descriptor=open('fileQ51',O_RDWR|O_CREAT|O_EXCL);
    return 0;
}