// //5. Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
    // Create five new files
    int fd1 = open("fileQ5a",O_RDWR|O_CREAT|O_EXCL, 0744);
    printf("File descriptor 1: %d\n",fd1);
    int fd2 = open("fileQ5b",O_RDWR|O_CREAT|O_EXCL, 0744);
    printf("File descriptor 2: %d\n",fd2);
    int fd3 = open("fileQ5c",O_RDWR|O_CREAT|O_EXCL, 0744);
    printf("File descriptor 3: %d\n",fd3);
    int fd4 = open("fileQ5d",O_RDWR|O_CREAT|O_EXCL, 0744);
    printf("File descriptor 4: %d\n",fd4);
    int fd5 = open("fileQ5e",O_RDWR|O_CREAT|O_EXCL, 0744);
    printf("File descriptor 5: %d\n",fd5);

    for(;;);

    return 0;
}