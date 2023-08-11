#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	// take input from command line
	int v = symlink("dest","destSL");
	if(v<0)
	{
		perror("failed");return 1;	
	}
	int f = link("dest","destHL");
	if(f<0)
	{
		perror("failed");return 1;
	}
	int e = mknod("destFIFO",S_IFIFO,0);
        if(e<0)
	{
		perror("failed");return 1;
	}	
	return 0;
}
