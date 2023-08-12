// //5. Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    FILE *fileQ[5];
    for(int i=0;i<5;i++)
    {
        char filename[20];
        sprintf(filename,"fileQ%d",i);
        fileQ[i]=fopen(filename,"w");
        if(fileQ[i]==NULL)
        {
            perror("Failed to create a file");
            exit(1);
        }
    }
        while(1)
        {   
            //fprintf(fileQ[i],"This is the file");
            sleep(15);
        }
    for(int i=0;i<5;i++)
    {
        fclose(fileQ[i]);
    }
    return 0;
}