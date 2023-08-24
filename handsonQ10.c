/*
10. Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
 a. check the return value of lseek
 b. open the file with od and check the empty spaces in between the data.
*/
#include<stdio.h>   
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
    int fd_read;
    fd_read=open("fileQ10",O_RDWR|O_CREAT,0666);
    if (fd_read<0)
    {
        perror("error in opening a file");
        return 0;
    }
    int return_write = write(fd_read,"space of 10 bytes ",sizeof("space of 10 bytes "));
    if (return_write<0)
    {
        perror("write error");
        return 0;
    }
    off_t return_lseek = lseek(fd_read,10,SEEK_CUR);
    return_write=write(fd_read,"second time typing 10 bytes",sizeof("second time typing 10 bytes"));
    if (return_write<0)
    {
        perror("write error");
        return 0;
    }
    printf("the return value of lseek is %ld\n",return_lseek);
    return 0;
}