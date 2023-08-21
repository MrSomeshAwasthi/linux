// 8. Write a program to open a file in read only mode, read line by line and display each line as it is read.
// Close the file when end of file is reached.
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int a;
    int file_discriptor=open("fileQ8",O_RDONLY);
    char buffer[1024];
    if (file_discriptor<0)
    {
        perror("file is empty");
        return 1;
    }
    //ssize_t read(int fd, void buf[.count], size_t count);
    while ((a=read(file_discriptor,buffer,1024))>0)
    {   
        if (buffer[a-1]=='\n')
            buffer[a-1]='\0';
        printf("%s\n",buffer);
    }
    int fd_close=close(file_discriptor);
    return 0;
}