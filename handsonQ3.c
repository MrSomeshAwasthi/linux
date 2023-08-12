//3. Write a program to create a file and print the file descriptor value. Use creat ( ) system call
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
    int file_discriptor = creat("fileQ3.txt",0666);
    if(file_discriptor<0)
    {
        perror("error in creating a file");
        return 1;
    }
    printf("the file has been created successfully\n");
    printf("the file descriptor : %d\n",file_discriptor);
    close(file_discriptor);
    return 0;
}
