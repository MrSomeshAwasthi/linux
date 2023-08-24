// 4. Write a program to open an existing file with read write mode. Try O_EXCL flag also. 
#include<stdio.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
const char *filename="fileQ4.txt";
const char *data="Now Im writing through CLI";
int file_descriptor=open(filename,O_WRONLY | O_EXCL, 0666);
write(file_descriptor,data,strlen(data));
if(file_descriptor<0)
{
    perror("error in opening file");
    return 1;
}
close(file_descriptor);
return 0;
}