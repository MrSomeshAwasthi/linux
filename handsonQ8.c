// 8. Write a program to open a file in read only mode, read line by line and display each line as it is read.
// Close the file when end of file is reached.
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int a;
    int file_descriptor=open("fileQ8",O_RDONLY);
    char buffer[1];
    if (file_descriptor<0)
    {
        perror("file is empty");
        return 1;
    }
    //ssize_t read(int fd, void buf[.count], size_t count);
    while ((a=read(file_descriptor,buffer,1))>0)
    {   
        if (buffer[0]=='\n')
            write(1,"\n\n",1);
        else
            write(1,buffer,1);
    }
    int fd_close=close(file_descriptor);
    return 0;
}