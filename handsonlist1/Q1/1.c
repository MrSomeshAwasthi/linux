/*
============================================================================
Name : 1.c
Author : Somesh Awasthi
Description :Create the following types of a files using (i) shell command (ii) system call
		a. soft link (symlink system call)
 		b. hard link (link system call)
		c. FIFO (mkfifo Library Function or mknod system call)
Date: 28th Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	// creating a soft link
	if (symlink("fileQ1.txt","sl")<0) //it create a softlink
	{
		perror("error in creating a soft link\n");//this function will print specific error
		return 1;
	}
	if (link("fileQ1.txt","hl")<0)	// it will create a hardlink
	{
		perror("error in creating a hard link\n");
		return 1;
	}
	if (mkfifo("pipe",0666)<0)
	{
		perror("error in creating a Fifo\n");
		return 1;
	}
	printf("softlink, hardlink, fifo created successfully.\n");
	return 0;
}
