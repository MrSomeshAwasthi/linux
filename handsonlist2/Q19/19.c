/*
==================================================================================================
Name : 19.c
Author : Somesh Awasthi
Description :  Create a FIFO file by    
                a. mknod command    
                b. mkfifo command    
                c. use strace command to find out, which command (mknod or mkfifo) is better.    
                d. mknod system call    
                e. mkfifo library function  
Date: 1st oct, 2023.
==================================================================================================
*/

/*
solution
a: mknod "pipe2" p  
b: mkfifo "pipe1"
c: 1>strace -c mknod "pipe2" p
   2>strace -c mkfifo "pipe1" 
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
 #include<sys/stat.h>
// #include<sys/types.h>
int main()
{
    if (mkfifo("pipe3",0666)==-1)
    {
        perror("pipe error(mkfifo)");
        return 0;
    }
    if(mknod("pipe4", __S_IFIFO | 0666,0)==-1)
    {
        perror("pipe error");
        return 0;
    }
    return 0;
}