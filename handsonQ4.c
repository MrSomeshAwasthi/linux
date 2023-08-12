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
int file_discriptor=open(filename,O_WRONLY | O_EXCL, 0666);
write(file_discriptor,data,strlen(data));
if(file_discriptor<0)
{
    perror("error in opening file");
    return 1;
}
close(file_discriptor);
return 0;
}