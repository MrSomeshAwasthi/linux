/* 
13. Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select). 
*/ 
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/select.h> 
int main() 
{ 
    fd_set rd; 
    struct timeval tv; 
    int return_val = 0; 
    // Initialize the readfds set 
    FD_ZERO(&rd); 
    FD_SET(0, &rd); 
    // Set the timeout 
    tv.tv_sec = 10;             
    tv.tv_usec = 0; 
    // Wait for data on STDIN 
    return_val = select(1, &rd, NULL, NULL, &tv); 
    printf("%d",return_val); 
    // Check the select result 
    if (return_val<0) 
    {
        perror("select");
        return 1; 
    } 
    if (return_val)
        printf("Data available within 10 seconds \n");
    else 
        printf("Data available within 10 seconds\n"); 
    return 0; 
}