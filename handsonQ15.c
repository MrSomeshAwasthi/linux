/*
15. Write a program to display the environmental variable of the user (use environ).
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    extern char **environ;
    while(*environ)
    {
        if(strncmp(*environ,"USER",4)==0)
            printf("%s\n",*environ);
        environ++;
    }
    return 0;
}