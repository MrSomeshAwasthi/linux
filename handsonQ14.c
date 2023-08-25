/*
14 Write a program to find the type of a file.
 a. Input should be taken from command line.
 b. program should be able to identify any type of a file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {    
        perror("error please give proper input");
        return 0;
    }

    struct stat sb;
    //stat is use for retriving info of file and dir.
    int status = stat(argv[1],&sb);
    if (status < 0)
    {
        perror("stat");
        return 1;
    }
    if (S_ISREG(sb.st_mode))
        printf("Regular file\n");
    else if (S_ISDIR(sb.st_mode))
        printf("Directory\n");
    else if (S_ISBLK(sb.st_mode)) 
        printf("Block device\n");
    else if (S_ISCHR(sb.st_mode)) 
        printf("Character device\n");
    else if (S_ISFIFO(sb.st_mode)) 
        printf("FIFO\n");
    else if (S_ISSOCK(sb.st_mode)) 
        printf("Socket\n");
    return 0;
}
