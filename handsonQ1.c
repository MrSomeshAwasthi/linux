// including important header file like stdio for i/o and 
// stdlib for memory management (sys/types,sys/stat,fcntl) for file and directory management
// and for system call unistd
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>//mainly used for fifo
#include<sys/stat.h>// mainly used for fifo
#include<fcntl.h>
int main()
{
	// creating a soft link
	if (symlink("my_file.txt","sl")<0) //it create a softlink
	{
		perror("error in creating a soft link\n");//this function will print specific error
		return 1;
	}
	if (link("my_file.txt","hl")<0)	// it will create a hardlink
	{
		perror("error in creating a hard link\n");
		return 1;
	}
	if (mknod("my_file1.txt",S_IFIFO,0)<0)
	{
		perror("error in creating a Fifo\n");
		return 1;
	}
	printf("softlink, hardlink, fifo created successfully.\n");
	return 0;
}
